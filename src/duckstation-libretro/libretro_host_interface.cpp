#include "libretro_host_interface.h"
#include "common/assert.h"
#include "common/byte_stream.h"
#include "common/platform.h"
#include "common/file_system.h"
#include "common/log.h"
#include "common/string_util.h"
#include "core/analog_controller.h"
#include "core/bus.h"
#include "core/cheats.h"
#include "core/digital_controller.h"
#include "core/gpu.h"
#include "core/system.h"
#include "core/pad.h"
#include "libretro_audio_stream.h"
#include "libretro_game_settings.h"
#include "libretro_host_display.h"
#include "libretro_opengl_host_display.h"
#include "libretro_settings_interface.h"
#include "libretro_vulkan_host_display.h"
#include <array>
#include <cstring>
#include <tuple>
#include <utility>
#include <vector>
Log_SetChannel(LibretroHostInterface);

#ifdef WIN32
#include "libretro_d3d11_host_display.h"
#endif

LibretroHostInterface g_libretro_host_interface;
#define P_THIS (&g_libretro_host_interface)

retro_environment_t g_retro_environment_callback;
retro_video_refresh_t g_retro_video_refresh_callback;
retro_audio_sample_t g_retro_audio_sample_callback;
retro_audio_sample_batch_t g_retro_audio_sample_batch_callback;
retro_input_poll_t g_retro_input_poll_callback;
retro_input_state_t g_retro_input_state_callback;

static retro_log_callback s_libretro_log_callback = {};
static bool s_libretro_log_callback_valid = false;
static bool s_libretro_log_callback_registered = false;
static std::array<ControllerType, NUM_CONTROLLER_AND_CARD_PORTS> s_controller_types{};

static void LibretroLogCallback(void* pUserParam, const char* channelName, const char* functionName, LOGLEVEL level,
                                const char* message)
{
  static constexpr std::array<retro_log_level, LOGLEVEL_COUNT> levels = {
    {RETRO_LOG_ERROR, RETRO_LOG_ERROR, RETRO_LOG_WARN, RETRO_LOG_INFO, RETRO_LOG_INFO, RETRO_LOG_INFO, RETRO_LOG_DEBUG,
     RETRO_LOG_DEBUG, RETRO_LOG_DEBUG, RETRO_LOG_DEBUG}};

  s_libretro_log_callback.log(levels[level], "[%s] %s\n", (level <= LOGLEVEL_PERF) ? functionName : channelName,
                              message);
}

LibretroHostInterface::LibretroHostInterface() = default;

LibretroHostInterface::~LibretroHostInterface()
{
  // a few things we are safe to cleanup because these pointers are garaunteed to be initialized to zero (0)
  // when the shared library (dll/so) is loaded into memory. Other things are not safe, such as calling
  // HostInterface::Shutdown, because it depends on a bunch of vars being initialized to zero at runtime,
  // otherwise it thinks it needs to clean them up and they're actually invalid, and crashes happen.

  m_audio_stream.reset();   // assert checks will expect this is nullified.
  ReleaseHostDisplay();     // assert checks will expect this is nullified.
}

void LibretroHostInterface::retro_set_environment()
{
  SetCoreOptions();
  InitLogging();
}

void LibretroHostInterface::InitInterfaces()
{
  InitRumbleInterface();
  InitDiskControlInterface();

  unsigned dummy = 0;
  m_supports_input_bitmasks = g_retro_environment_callback(RETRO_ENVIRONMENT_GET_INPUT_BITMASKS, &dummy);
}

void LibretroHostInterface::InitLogging()
{
  if (s_libretro_log_callback_registered)
    return;

  s_libretro_log_callback_valid =
    g_retro_environment_callback(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &s_libretro_log_callback);

  if (s_libretro_log_callback_valid)
  {
    Log::RegisterCallback(LibretroLogCallback, nullptr);
    s_libretro_log_callback_registered = true;
  }

  // this is a windows/android specific concept, of logging to an attached debugger.
  // on unix systems this doesn't do anything, though arguably it should enable logging to stdout.
  Log::SetDebugOutputParams(g_settings.log_to_debug);
}

bool LibretroHostInterface::Initialize()
{
  if (!HostInterface::Initialize())
    return false;

  /* Reset disk control info struct */
  P_THIS->m_disk_control_info.has_sub_images      = false;
  P_THIS->m_disk_control_info.initial_image_index = 0;
  P_THIS->m_disk_control_info.image_index         = 0;
  P_THIS->m_disk_control_info.image_count         = 0;
  P_THIS->m_disk_control_info.sub_images_parent_path.clear();
  P_THIS->m_disk_control_info.image_paths.clear();
  P_THIS->m_disk_control_info.image_labels.clear();

  InitInterfaces();
  LibretroSettingsInterface si;
  LoadSettings(si);
  FixIncompatibleSettings(true);
  UpdateLogging();

  m_last_aspect_ratio = g_settings.GetDisplayAspectRatioValue();
  m_last_width = 320;
  m_last_height = 240;
  return true;
}

void LibretroHostInterface::Shutdown()
{
  HostInterface::Shutdown();

  /* Reset disk control info struct */
  P_THIS->m_disk_control_info.has_sub_images      = false;
  P_THIS->m_disk_control_info.initial_image_index = 0;
  P_THIS->m_disk_control_info.image_index         = 0;
  P_THIS->m_disk_control_info.image_count         = 0;
  P_THIS->m_disk_control_info.sub_images_parent_path.clear();
  P_THIS->m_disk_control_info.image_paths.clear();
  P_THIS->m_disk_control_info.image_labels.clear();
}

void LibretroHostInterface::ReportError(const char* message)
{
  AddFormattedOSDMessage(10.0f, "ERROR: %s", message);
  Log_ErrorPrint(message);
}

void LibretroHostInterface::ReportMessage(const char* message)
{
  AddOSDMessage(message, 5.0f);
  Log_InfoPrint(message);
}

bool LibretroHostInterface::ConfirmMessage(const char* message)
{
  Log_InfoPrintf("Confirm: %s", message);
  return false;
}

void LibretroHostInterface::GetGameInfo(const char* path, CDImage* image, std::string* code, std::string* title)
{
  // Just use the filename for now... we don't have the game list. Unless we can pull this from the frontend somehow?
  *title = FileSystem::GetFileTitleFromPath(path);
  *code = System::GetGameCodeForImage(image, true);
}

static const char* GetSaveDirectory()
{
  const char* save_directory = nullptr;
  if (!g_retro_environment_callback(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_directory) || !save_directory)
    save_directory = "saves";

  return save_directory;
}

std::string LibretroHostInterface::GetSharedMemoryCardPath(u32 slot) const
{
  return StringUtil::StdStringFromFormat("%s" FS_OSPATH_SEPARATOR_STR "duckstation_shared_card_%d.mcd",
                                         GetSaveDirectory(), slot + 1);
}

std::string LibretroHostInterface::GetGameMemoryCardPath(const char* game_code, u32 slot) const
{
  return StringUtil::StdStringFromFormat("%s" FS_OSPATH_SEPARATOR_STR "%s_%d.mcd", GetSaveDirectory(), game_code,
                                         slot + 1);
}

std::string LibretroHostInterface::GetShaderCacheBasePath() const
{
  // Use the save directory, and failing that, the system directory.
  const char* save_directory_ptr = nullptr;
  if (!g_retro_environment_callback(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_directory_ptr) || !save_directory_ptr)
  {
    save_directory_ptr = nullptr;
    if (!g_retro_environment_callback(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &save_directory_ptr) ||
        !save_directory_ptr)
    {
      Log_WarningPrint("No shader cache directory available, startup will be slower.");
      return std::string();
    }
  }

  // Use a directory named "duckstation_cache" in the save/system directory.
  std::string shader_cache_path = StringUtil::StdStringFromFormat(
    "%s" FS_OSPATH_SEPARATOR_STR "duckstation_cache" FS_OSPATH_SEPARATOR_STR, save_directory_ptr);
  if (!FileSystem::DirectoryExists(shader_cache_path.c_str()) &&
      !FileSystem::CreateDirectory(shader_cache_path.c_str(), false))
  {
    Log_ErrorPrintf("Failed to create shader cache directory: '%s'", shader_cache_path.c_str());
    return std::string();
  }

  Log_InfoPrintf("Shader cache directory: '%s'", shader_cache_path.c_str());
  return shader_cache_path;
}

std::string LibretroHostInterface::GetStringSettingValue(const char* section, const char* key,
                                                         const char* default_value /*= ""*/)
{
  TinyString name;
  name.Format("duckstation_%s.%s", section, key);
  retro_variable var{name, default_value};
  if (g_retro_environment_callback(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    return var.value;
  else
    return default_value;
}

void LibretroHostInterface::AddOSDMessage(std::string message, float duration /*= 2.0f*/)
{
  if (!g_settings.display_show_osd_messages)
    return;

  retro_message msg = {};
  msg.msg = message.c_str();
  msg.frames = static_cast<u32>(duration * (System::IsShutdown() ? 60.0f : System::GetThrottleFrequency()));
  g_retro_environment_callback(RETRO_ENVIRONMENT_SET_MESSAGE, &msg);
}

void LibretroHostInterface::retro_get_system_av_info(struct retro_system_av_info* info)
{
  const bool use_resolution_scale = (g_settings.gpu_renderer != GPURenderer::Software);
  GetSystemAVInfo(info, use_resolution_scale);

  Log_InfoPrintf("base = %ux%u, max = %ux%u, aspect ratio = %.2f, fps = %.2f", info->geometry.base_width,
                 info->geometry.base_height, info->geometry.max_width, info->geometry.max_height,
                 info->geometry.aspect_ratio, info->timing.fps);
}

void LibretroHostInterface::GetSystemAVInfo(struct retro_system_av_info* info, bool use_resolution_scale)
{
  const u32 resolution_scale = use_resolution_scale ? g_settings.gpu_resolution_scale : 1u;
  Assert(System::IsValid());

  std::memset(info, 0, sizeof(*info));

  const auto [effective_width, effective_height] = g_gpu->GetEffectiveDisplayResolution();

  info->geometry.aspect_ratio = m_last_aspect_ratio;
  info->geometry.base_width = effective_width;
  info->geometry.base_height = effective_height;
  info->geometry.max_width = VRAM_WIDTH * resolution_scale;
  info->geometry.max_height = VRAM_HEIGHT * resolution_scale;

  info->timing.fps = System::GetThrottleFrequency();
  info->timing.sample_rate = static_cast<double>(AUDIO_SAMPLE_RATE);
}

bool LibretroHostInterface::UpdateSystemAVInfo(bool use_resolution_scale)
{
  struct retro_system_av_info avi;
  GetSystemAVInfo(&avi, use_resolution_scale);

  Log_InfoPrintf("base = %ux%u, max = %ux%u, aspect ratio = %.2f, fps = %.2f", avi.geometry.base_width,
                 avi.geometry.base_height, avi.geometry.max_width, avi.geometry.max_height, avi.geometry.aspect_ratio,
                 avi.timing.fps);

  if (!g_retro_environment_callback(RETRO_ENVIRONMENT_SET_SYSTEM_AV_INFO, &avi))
  {
    Log_ErrorPrintf("Failed to update system AV info on resolution change");
    return false;
  }

  return true;
}

void LibretroHostInterface::UpdateGeometry()
{
  struct retro_system_av_info avi;
  const bool use_resolution_scale = (g_settings.gpu_renderer != GPURenderer::Software);
  GetSystemAVInfo(&avi, use_resolution_scale);

  Log_InfoPrintf("base = %ux%u, max = %ux%u, aspect ratio = %.2f", avi.geometry.base_width, avi.geometry.base_height,
                 avi.geometry.max_width, avi.geometry.max_height, avi.geometry.aspect_ratio);

  if (!g_retro_environment_callback(RETRO_ENVIRONMENT_SET_GEOMETRY, &avi.geometry))
    Log_WarningPrint("RETRO_ENVIRONMENT_SET_GEOMETRY failed");
}

void LibretroHostInterface::UpdateLogging()
{
  Log::SetFilterLevel(g_settings.log_level);

  if (s_libretro_log_callback_valid)
    Log::SetConsoleOutputParams(false);
  else
    Log::SetConsoleOutputParams(true, nullptr, g_settings.log_level);
}

bool LibretroHostInterface::UpdateGameSettings()
{
  std::unique_ptr<GameSettings::Entry> new_game_settings;

  if (!System::IsShutdown() && !System::GetRunningCode().empty())
  {
    new_game_settings = GetSettingsForGame(System::GetRunningCode());
    if (new_game_settings)
      Log_InfoPrintf("Game settings found for %s", System::GetRunningCode().c_str());
  }

  if (new_game_settings == m_game_settings)
    return false;

  m_game_settings = std::move(new_game_settings);
  return true;
}

void LibretroHostInterface::ApplyGameSettings()
{
  if (!g_settings.apply_game_settings || !m_game_settings)
    return;

  m_game_settings->ApplySettings(System::GetState() == System::State::Starting);
}

bool LibretroHostInterface::retro_load_game(const struct retro_game_info* game)
{
  auto bp = std::make_shared<SystemBootParameters>();
  bp->filename = game->path;
  bp->media_playlist_index = P_THIS->m_disk_control_info.initial_image_index;
  bp->force_software_renderer = !m_hw_render_callback_valid;

  struct retro_input_descriptor desc[] = {
#define JOYP(port)                                                                                                     \
  {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left"},                                           \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up"},                                             \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down"},                                         \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right"},                                       \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Cross"},                                                 \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Circle"},                                                \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Triangle"},                                              \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Square"},                                                \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L1"},                                                    \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "L2"},                                                   \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L3, "L3"},                                                   \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R1"},                                                    \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "R2"},                                                   \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "R3"},                                                   \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select"},                                           \
    {port, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start"},                                             \
    {port, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Left Analog X"},            \
    {port, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Left Analog Y"},            \
    {port, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "Right Analog X"},          \
    {port, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y, "Right Analog Y"},

    JOYP(0) JOYP(1) JOYP(2) JOYP(3) JOYP(4) JOYP(5) JOYP(6) JOYP(7)

      {0},
  };

  g_retro_environment_callback(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);

  if (!BootSystem(std::move(bp)))
    return false;

  if (g_settings.gpu_renderer != GPURenderer::Software)
  {
    if (!m_hw_render_callback_valid)
      RequestHardwareRendererContext();
    else
      SwitchToHardwareRenderer();
  }

  /* Initialise disk control info struct */
  if (System::HasMedia())
  {
    if (System::HasMediaSubImages())
    {
      const std::string& parent_path = System::GetMediaFileName();
      if (parent_path.empty())
        return false;

      P_THIS->m_disk_control_info.has_sub_images         = true;
      P_THIS->m_disk_control_info.image_index            = System::GetMediaSubImageIndex();
      P_THIS->m_disk_control_info.image_count            = System::GetMediaSubImageCount();
      P_THIS->m_disk_control_info.sub_images_parent_path = parent_path;

      for (u32 i = 0; i < P_THIS->m_disk_control_info.image_count; i++)
      {
        const std::string& sub_image_path = System::GetMediaSubImagePath(i);
        if (sub_image_path.empty())
          return false;

        const std::string& sub_image_label = System::GetMediaSubImageTitle(i);
        if (sub_image_label.empty())
          return false;

        P_THIS->m_disk_control_info.image_paths.push_back(sub_image_path);
        P_THIS->m_disk_control_info.image_labels.push_back(sub_image_label);
      }
    }
    else
    {
      const std::string& image_path = System::GetMediaFileName();
      if (image_path.empty())
        return false;

      const std::string_view image_label = FileSystem::GetFileTitleFromPath(image_path);
      if (image_label.empty())
        return false;

      P_THIS->m_disk_control_info.has_sub_images = false;
      P_THIS->m_disk_control_info.image_index    = 0;
      P_THIS->m_disk_control_info.image_count    = 1;
      P_THIS->m_disk_control_info.sub_images_parent_path.clear();

      P_THIS->m_disk_control_info.image_paths.push_back(image_path);
      P_THIS->m_disk_control_info.image_labels.push_back(std::string(image_label));
    }
  }

  return true;
}

void LibretroHostInterface::retro_run_frame()
{
  Assert(!System::IsShutdown());

  if (HasCoreVariablesChanged())
    UpdateSettings();

  UpdateControllers();

  System::RunFrame();

  const float aspect_ratio = m_display->GetDisplayAspectRatio();
  const auto [effective_width, effective_height] = g_gpu->GetEffectiveDisplayResolution();

  if (aspect_ratio != m_last_aspect_ratio || effective_width != m_last_width || effective_height != m_last_height)
  {
    m_last_aspect_ratio = aspect_ratio;
    m_last_width = effective_width;
    m_last_height = effective_height;
    UpdateGeometry();
  }

  m_display->Render();
}

unsigned LibretroHostInterface::retro_get_region()
{
  return System::IsPALRegion() ? RETRO_REGION_PAL : RETRO_REGION_NTSC;
}

size_t LibretroHostInterface::retro_serialize_size()
{
  return System::MAX_SAVE_STATE_SIZE;
}

bool LibretroHostInterface::retro_serialize(void* data, size_t size)
{
  std::unique_ptr<ByteStream> stream = ByteStream_CreateMemoryStream(data, static_cast<u32>(size));
  if (!System::SaveState(stream.get(), 0))
  {
    Log_ErrorPrintf("Failed to save state to memory stream");
    return false;
  }

  return true;
}

bool LibretroHostInterface::retro_unserialize(const void* data, size_t size)
{
  std::unique_ptr<ByteStream> stream = ByteStream_CreateReadOnlyMemoryStream(data, static_cast<u32>(size));
  if (!System::LoadState(stream.get(), false))
  {
    Log_ErrorPrintf("Failed to load save state from memory stream");
    return false;
  }

  return true;
}

void* LibretroHostInterface::retro_get_memory_data(unsigned id)
{
  switch (id)
  {
    case RETRO_MEMORY_SYSTEM_RAM:
      return System::IsShutdown() ? nullptr : Bus::g_ram;

    case RETRO_MEMORY_SAVE_RAM: {
      const MemoryCardType type = g_settings.memory_card_types[0];
      if (System::IsShutdown()  || type != MemoryCardType::Libretro) {
        return nullptr;
      }
      auto card = g_pad.GetMemoryCard(0);
      auto& data = card->GetData();
      return data.data();
      break;
    }

    default:
      return nullptr;
  }
}

size_t LibretroHostInterface::retro_get_memory_size(unsigned id)
{
  switch (id)
  {
    case RETRO_MEMORY_SYSTEM_RAM:
      return Bus::g_ram_size;

    case RETRO_MEMORY_SAVE_RAM: {
      const MemoryCardType type = g_settings.memory_card_types[0];
      if (System::IsShutdown()  || type != MemoryCardType::Libretro) {
        return 0;
      }
      return 128 * 1024;
    }

    default:
      return 0;
  }
}

void LibretroHostInterface::retro_cheat_reset()
{
  System::SetCheatList(nullptr);
}

void LibretroHostInterface::retro_cheat_set(unsigned index, bool enabled, const char* code)
{
  CheatList* cl = System::GetCheatList();
  if (!cl)
  {
    System::SetCheatList(std::make_unique<CheatList>());
    cl = System::GetCheatList();
  }

  CheatCode cc;
  cc.description = StringUtil::StdStringFromFormat("Cheat%u", index);
  cc.enabled = true;
  if (!CheatList::ParseLibretroCheat(&cc, code))
    Log_ErrorPrintf("Failed to parse cheat %u '%s'", index, code);

  cl->SetCode(index, std::move(cc));
}

bool LibretroHostInterface::AcquireHostDisplay()
{
  // start in software mode, switch to hardware later
  m_display = std::make_unique<LibretroHostDisplay>();
  return true;
}

void LibretroHostInterface::ReleaseHostDisplay()
{
  if (m_hw_render_display)
  {
    m_hw_render_display->DestroyRenderDevice();
    m_hw_render_display.reset();
    m_using_hardware_renderer = false;
  }

  if (m_display)
  {
    m_display->DestroyRenderDevice();
    m_display.reset();
  }
}

std::unique_ptr<AudioStream> LibretroHostInterface::CreateAudioStream(AudioBackend backend)
{
  return std::make_unique<LibretroAudioStream>();
}

void LibretroHostInterface::OnSystemDestroyed()
{
  HostInterface::OnSystemDestroyed();
}

static std::array<retro_core_option_definition, 66> s_option_definitions = {{
  {"duckstation_Console.Region",
   "Console Region",
   "Determines which region/hardware to emulate. Auto-Detect will use the region of the disc inserted.",
   {{"Auto", "Auto-Detect"},
    {"NTSC-J", "NTSC-J (Japan)"},
    {"NTSC-U", "NTSC-U/C (US, Canada)"},
    {"PAL", "PAL (Europe, Australia)"}},
   "Auto"},
  {"duckstation_BIOS.PatchFastBoot",
   "Fast Boot",
   "Skips the BIOS shell/intro, booting directly into the game. Usually safe to enable, but some games break.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_CDROM.RegionCheck",
   "CD-ROM Region Check",
   "Prevents discs from incorrect regions being read by the emulator. Usually safe to disable.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_CDROM.ReadThread",
   "CD-ROM Read Thread",
   "Reads CD-ROM sectors ahead asynchronously, reducing the risk of frame time spikes.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "true"},
  {"duckstation_CDROM.LoadImageToRAM",
   "Preload CD-ROM Image To RAM",
   "Loads the disc image to RAM before starting emulation. May reduce hitching if you are running off a network share, "
   "at a cost of a greater startup time. As libretro provides no way to draw overlays, the emulator will appear to "
   "lock up while the image is preloaded.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_CDROM.MuteCDAudio",
   "Mute CD Audio",
   "Forcibly mutes both CD-DA and XA audio from the CD-ROM. Can be used to disable background music in some games.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_CDROM.ReadSpeedup",
   "CD-ROM Read Speedup",
   "Speeds up CD-ROM reads by the specified factor. Only applies to double-speed reads, and is ignored when audio "
   "is playing. May improve loading speeds in some games, at the cost of breaking others.",
   {{"1", "None (Double Speed)"},
    {"2", "2x (Quad Speed)"},
    {"3", "3x (6x Speed)"},
    {"4", "4x (8x Speed)"},
    {"5", "5x (10x Speed)"},
    {"6", "6x (12x Speed)"},
    {"7", "7x (14x Speed)"},
    {"8", "8x (16x Speed)"},
    {"9", "9x (18x Speed)"},
    {"10", "10x (20x Speed)"}},
   "1"},
  {"duckstation_CPU.ExecutionMode",
   "CPU Execution Mode",
   "Which mode to use for CPU emulation. Recompiler provides the best performance.",
   {{"Interpreter", "Interpreter"}, {"CachedInterpreter", "Cached Interpreter"}, {"Recompiler", "Recompiler"}},
   "Recompiler"},
  {"duckstation_CPU.Overclock",
   "CPU Overclocking",
   "Runs the emulated CPU faster or slower than native speed, which can improve framerates in some games. Will break "
   "other games and increase system requirements, use with caution.",
   {{"25", "25%"},   {"50", "50%"},   {"100", "100% (Default)"}, {"125", "125%"}, {"150", "150%"},
    {"175", "175%"}, {"200", "200%"}, {"225", "225%"},           {"250", "250%"}, {"275", "275%"},
    {"300", "300%"}, {"350", "350%"}, {"400", "400%"},           {"450", "450%"}, {"500", "500%"},
    {"600", "600%"}, {"700", "700%"}, {"800", "800%"},           {"900", "900%"}, {"1000", "1000%"}},
   "100"},
  {"duckstation_GPU.Renderer",
   "GPU Renderer",
   "Which renderer to use to emulate the GPU",
   {{"Auto", "Hardware (Auto)"},
#ifdef WIN32
    {"D3D11", "Hardware (D3D11)"},
#endif
    {"OpenGL", "Hardware (OpenGL)"},
    {"Vulkan", "Hardware (Vulkan)"},
    {"Software", "Software"}},
#ifdef WIN32
   "D3D11"
#else
   "OpenGL"
#endif
  },
  {"duckstation_GPU.UseThread",
   "Threaded Rendering (Software)",
   "Uses a second thread for drawing graphics. Currently only available for the software renderer.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "true"},
  {"duckstation_GPU.ResolutionScale",
   "Internal Resolution Scale",
   "Scales internal VRAM resolution by the specified multiplier. Larger values are slower. Some games require "
   "1x VRAM resolution or they will have rendering issues. Software render supports only 1x, 2x, 4x.",
   {{"1", "1x"},
    {"2", "2x"},
    {"3", "3x (for 720p)"},
    {"4", "4x"},
    {"5", "5x (for 1080p)"},
    {"6", "6x (for 1440p)"},
    {"7", "7x"},
    {"8", "8x"},
    {"9", "9x (for 4K)"},
    {"10", "10x"},
    {"11", "11x"},
    {"12", "12x"},
    {"13", "13x"},
    {"14", "14x"},
    {"15", "15x"},
    {"16", "16x"}},
   "1"},
  {"duckstation_GPU.MSAA",
   "Multisample Antialiasing",
   "Uses multisample antialiasing for rendering 3D objects. Can smooth out jagged edges on polygons at a lower "
   "cost to performance compared to increasing the resolution scale, but may be more likely to cause rendering "
   "errors in some games.",
   {{"1", "Disabled"},
    {"2", "2x MSAA"},
    {"4", "4x MSAA"},
    {"8", "8x MSAA"},
    {"16", "16x MSAA"},
    {"32", "32x MSAA"},
    {"2-ssaa", "2x SSAA"},
    {"4-ssaa", "4x SSAA"},
    {"8-ssaa", "8x SSAA"},
    {"16-ssaa", "16x SSAA"},
    {"32-ssaa", "32x SSAA"}},
   "1"},
  {"duckstation_GPU.TrueColor",
   "True Color Rendering",
   "Disables dithering and uses the full 8 bits per channel of color information. May break rendering in some games.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.ScaledDithering",
   "Scaled Dithering",
   "Scales the dithering pattern with the internal rendering resolution, making it less noticeable. Usually safe to "
   "enable.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "true"},
  {"duckstation_GPU.DisableInterlacing",
   "Disable Interlacing",
   "Disables interlaced rendering and display in the GPU. Some games can render in 480p this way, but others will "
   "break.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.ForceNTSCTimings",
   "Force NTSC Timings",
   "Forces PAL games to run at NTSC timings, i.e. 60hz. Some PAL games will run at their \"normal\" speeds, while "
   "others will break.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Display.Force4_3For24Bit",
   "Force 4:3 For 24-Bit Display",
   "Switches back to 4:3 display aspect ratio when displaying 24-bit content, usually FMVs.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.ChromaSmoothing24Bit",
   "Chroma Smoothing For 24-Bit Display",
   "Smooths out blockyness between colour transitions in 24-bit content, usually FMVs. Only applies to the hardware "
   "renderers.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.TextureFilter",
   "Texture Filtering",
   "Smooths out the blockyness of magnified textures on 3D object by using bilinear filtering. Will have a "
   "greater effect on higher resolution scales. Only applies to the hardware renderers.",
   {{"Nearest", "Nearest-Neighbor"},
    {"Bilinear", "Bilinear"},
    {"BilinearBinAlpha", "Bilinear (No Edge Blending)"},
    {"JINC2", "JINC2"},
    {"JINC2BinAlpha", "JINC2 (No Edge Blending)"},
    {"xBR", "xBR"},
    {"xBRBinAlpha", "xBR (No Edge Blending)"}},
   "Nearest"},
  {"duckstation_GPU.WidescreenHack",
   "Widescreen Hack",
   "Increases the field of view from 4:3 to the chosen display aspect ratio in 3D games. For 2D games, or games which "
   "use pre-rendered backgrounds, this enhancement will not work as expected.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.PGXPEnable",
   "PGXP Geometry Correction",
   "Reduces \"wobbly\" polygons by attempting to preserve the fractional component through memory transfers. Only "
   "works with the hardware renderers, and may not be compatible with all games.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.PGXPCulling",
   "PGXP Culling Correction",
   "Increases the precision of polygon culling, reducing the number of holes in geometry. Requires geometry correction "
   "enabled.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "true"},
  {"duckstation_GPU.PGXPTextureCorrection",
   "PGXP Texture Correction",
   "Uses perspective-correct interpolation for texture coordinates and colors, straightening out warped textures. "
   "Requires geometry correction enabled.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "true"},
  {"duckstation_GPU.PGXPDepthBuffer",
   "PGXP Depth Buffer",
   "Attempts to reduce polygon Z-fighting by testing pixels against the depth values from PGXP. Low compatibility, "
   "but can work well in some games. Requires geometry correction enabled.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.PGXPVertexCache",
   "PGXP Vertex Cache",
   "Uses screen coordinates as a fallback when tracking vertices through memory fails. May improve PGXP compatibility.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.PGXPCPU",
   "PGXP CPU Mode",
   "Tries to track vertex manipulation through the CPU. Some games require this option for PGXP to be effective. "
   "Very slow, and incompatible with the recompiler.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Display.AspectRatio",
   "Aspect Ratio",
   "Sets the core-provided aspect ratio.",
   {{"Auto", "Auto (Game Native)"},
    {"4:3", "4:3"},
    {"16:9", "16:9"},
    {"16:10", "16:10"},
    {"19:9", "19:9"},
    {"21:9", "21:9"},
    {"32:9", "32:9"},
    {"8:7", "8:7"},
    {"5:4", "5:4"},
    {"3:2", "3:2"},
    {"2:1 (VRAM 1:1)", "2:1 (VRAM 1:1)"},
    {"1:1", "1:1"},
    {"PAR 1:1", "PAR 1:1"}},
   "Auto"},
  {"duckstation_Display.CropMode",
   "Crop Mode",
   "Changes how much of the image is cropped. Some games display garbage in the overscan area which is typically "
   "hidden.",
   {{"None", "None"}, {"Overscan", "Only Overscan Area"}, {"Borders", "All Borders"}},
   "Overscan"},
  {"duckstation_GPU.DownsampleMode",
   "Downsampling",
   "Downsamples the rendered image prior to displaying it. Can improve overall image quality in mixed 2D/3D games, but "
   "should be disabled for pure 3D games. Only applies to the hardware renderers.",
   {{"Disabled", "Disabled"},
    {"Box", "Box (Downsample 3D/Smooth All)"},
    {"Adaptive", "Adaptive (Preserve 3D/Smooth 2D)"}},
   "Disabled"},
  {"duckstation_Main.LoadDevicesFromSaveStates",
   "Load Devices From Save States",
   "Sets whether the contents of devices and memory cards will be loaded when a save state is loaded.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_MemoryCards.Card1Type",
   "Memory Card 1 Type",
   "Sets the type of memory card for Slot 1.",
   {{"None", "No Memory Card"},
    {"Libretro", "Libretro"},
    {"Shared", "Shared Between All Games"},
    {"PerGame", "Separate Card Per Game (Game Code)"},
    {"PerGameTitle", "Separate Card Per Game (Game Title)"}},
   "Libretro"},
  {"duckstation_MemoryCards.Card2Type",
   "Memory Card 2 Type",
   "Sets the type of memory card for Slot 2.",
   {{"None", "No Memory Card"},
    {"Shared", "Shared Between All Games"},
    {"PerGame", "Separate Card Per Game (Game Code)"},
    {"PerGameTitle", "Separate Card Per Game (Game Title)"}},
   "None"},
  {"duckstation_MemoryCards.UsePlaylistTitle",
   "Use Single Card For Playlist",
   "When using a playlist (m3u) and per-game (title) memory cards, a single memory card "
   "will be used for all discs. If unchecked, a separate card will be used for each disc.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "true"},
  {"duckstation_ControllerPorts.MultitapMode",
   "Multitap Mode",
   "Sets the mode for the multitap",
   {{"Disabled", "Disabled"},
    {"Port1Only", "Enable on Port 1 Only"},
    {"Port2Only", "Enable on Port 2 Only"},
    {"BothPorts", "Enable on Ports 1 and 2"}},
   "Disabled"},
  {"duckstation_Controller1.Type",
   "Controller 1 Type",
   "Sets the type of controller for Slot 1.",
   {{"None", "None"},
    {"DigitalController", "Digital Controller"},
    {"AnalogController", "Analog Controller (DualShock)"}},
   "DigitalController"},
  {"duckstation_Controller1.ForceAnalogOnReset",
   "Controller 1 Force Analog Mode on Reset",
   "Forces analog mode in Analog Controller (DualShock) at start/reset. May cause issues with some games. Only use "
   "this option for games that support analog mode but do not automatically enable it themselves.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Controller1.AnalogDPadInDigitalMode",
   "Controller 1 Use Analog Sticks for D-Pad in Digital Mode",
   "Allows you to use the analog sticks to control the d-pad in digital mode, as well as the buttons.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Controller1.AxisScale",
   "Controller 1 Analog Axis Scale",
   "Sets the analog stick axis scaling factor.",
   {{"1.00f", "1.00"}, {"1.40f", "1.40"}},
   "1.00f"},
  {"duckstation_Controller2.Type",
   "Controller 2 Type",
   "Sets the type of controller for Slot 2.",
   {{"None", "None"},
    {"DigitalController", "Digital Controller"},
    {"AnalogController", "Analog Controller (DualShock)"}},
   "None"},
  {"duckstation_Controller2.ForceAnalogOnReset",
   "Controller 2 Force Analog Mode on Reset",
   "Forces analog mode in Analog Controller (DualShock) at start/reset. May cause issues with some games. Only use "
   "this option for games that support analog mode but do not automatically enable it themselves.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Controller2.AnalogDPadInDigitalMode",
   "Controller 2 Use Analog Sticks for D-Pad in Digital Mode",
   "Allows you to use the analog sticks to control the d-pad in digital mode, as well as the buttons.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Controller2.AxisScale",
   "Controller 2 Analog Axis Scale",
   "Sets the analog stick axis scaling factor.",
   {{"1.00f", "1.00"}, {"1.40f", "1.40"}},
   "1.00f"},
  {"duckstation_Controller3.Type",
   "Controller 3 Type",
   "Sets the type of controller for Slot 3.",
   {{"None", "None"},
    {"DigitalController", "Digital Controller"},
    {"AnalogController", "Analog Controller (DualShock)"}},
   "None"},
  {"duckstation_Controller3.ForceAnalogOnReset",
   "Controller 3 Force Analog Mode on Reset",
   "Forces analog mode in Analog Controller (DualShock) at start/reset. May cause issues with some games. Only use "
   "this option for games that support analog mode but do not automatically enable it themselves.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Controller3.AnalogDPadInDigitalMode",
   "Controller 3 Use Analog Sticks for D-Pad in Digital Mode",
   "Allows you to use the analog sticks to control the d-pad in digital mode, as well as the buttons.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Controller3.AxisScale",
   "Controller 3 Analog Axis Scale",
   "Sets the analog stick axis scaling factor.",
   {{"1.00f", "1.00"}, {"1.40f", "1.40"}},
   "1.00f"},
  {"duckstation_Controller4.Type",
   "Controller 4 Type",
   "Sets the type of controller for Slot 4.",
   {{"None", "None"},
    {"DigitalController", "Digital Controller"},
    {"AnalogController", "Analog Controller (DualShock)"}},
   "None"},
  {"duckstation_Controller4.ForceAnalogOnReset",
   "Controller 4 Force Analog Mode on Reset",
   "Forces analog mode in Analog Controller (DualShock) at start/reset. May cause issues with some games. Only use "
   "this option for games that support analog mode but do not automatically enable it themselves.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Controller4.AnalogDPadInDigitalMode",
   "Controller 4 Use Analog Sticks for D-Pad in Digital Mode",
   "Allows you to use the analog sticks to control the d-pad in digital mode, as well as the buttons.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_Controller4.AxisScale",
   "Controller 4 Analog Axis Scale",
   "Sets the analog stick axis scaling factor.",
   {{"1.00f", "1.00"}, {"1.40f", "1.40"}},
   "1.00f"},
  {"duckstation_Display.ShowOSDMessages",
   "Display OSD Messages",
   "Shows on-screen messages generated by the core.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "true"},
  {"duckstation_Main.ApplyGameSettings",
   "Apply Compatibility Settings",
   "Automatically disables enhancements on games which are incompatible.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "true"},
  {"duckstation_Logging.LogLevel",
   "Log Level",
   "Sets the level of information logged by the core.",
   {{"None", "None"},
    {"Error", "Error"},
    {"Warning", "Warning"},
    {"Perf", "Performance"},
    {"Info", "Information"},
    {"Verbose", "Verbose"},
    {"Dev", "Developer"},
    {"Profile", "Profile"},
    {"Debug", "Debug"},
    {"Trace", "Trace"}},
   "Info"},
  {"duckstation_CPU.RecompilerICache",
   "CPU Recompiler ICache",
   "Determines whether the CPU's instruction cache is simulated in the recompiler. Improves accuracy at a small cost "
   "to performance. If games are running too fast, try enabling this option.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_CPU.FastmemMode",
   "CPU Recompiler Fast Memory Access",
   "Uses page faults to determine hardware memory accesses at runtime. Can provide a significant performance "
   "improvement in some games, but make the core more difficult to debug.",
   {{"Disabled", "Disabled (Slowest)"}, {"MMap", "MMap (Hardware, Fastest, 64-Bit Only)"}, {"LUT", "LUT (Faster)"}},
   "LUT"},
  {"duckstation_Display.ActiveStartOffset",
   "Display Active Start Offset",
   "Pads or crops off lines from the left of the displayed image.",
   {{"-30", "-30"}, {"-29", "-29"}, {"-28", "-28"}, {"-27", "-27"}, {"-26", "-26"}, {"-25", "-25"}, {"-24", "-24"},
    {"-23", "-23"}, {"-22", "-22"}, {"-21", "-21"}, {"-20", "-20"}, {"-19", "-19"}, {"-18", "-18"}, {"-17", "-17"},
    {"-16", "-16"}, {"-15", "-15"}, {"-14", "-14"}, {"-13", "-13"}, {"-12", "-12"}, {"-11", "-11"}, {"-10", "-10"},
    {"-9", "-9"},   {"-8", "-8"},   {"-7", "-7"},   {"-6", "-6"},   {"-5", "-5"},   {"-4", "-4"},   {"-3", "-3"},
    {"-2", "-2"},   {"-1", "-1"},   {"0", "0"},     {"1", "1"},     {"2", "2"},     {"3", "3"},     {"4", "4"},
    {"5", "5"},     {"6", "6"},     {"7", "7"},     {"8", "8"},     {"9", "9"},     {"10", "10"},   {"11", "11"},
    {"12", "12"},   {"13", "13"},   {"14", "14"},   {"15", "15"},   {"16", "16"},   {"17", "17"},   {"18", "18"},
    {"19", "19"},   {"20", "20"},   {"21", "21"},   {"22", "22"},   {"23", "23"},   {"24", "24"},   {"25", "25"},
    {"26", "26"},   {"27", "27"},   {"28", "28"},   {"29", "29"},   {"30", "30"}},
   "0"},
  {"duckstation_Display.ActiveEndOffset",
   "Display Active End Offset",
   "Pads or crops off lines from the right of the displayed image.",
   {{"-30", "-30"}, {"-29", "-29"}, {"-28", "-28"}, {"-27", "-27"}, {"-26", "-26"}, {"-25", "-25"}, {"-24", "-24"},
    {"-23", "-23"}, {"-22", "-22"}, {"-21", "-21"}, {"-20", "-20"}, {"-19", "-19"}, {"-18", "-18"}, {"-17", "-17"},
    {"-16", "-16"}, {"-15", "-15"}, {"-14", "-14"}, {"-13", "-13"}, {"-12", "-12"}, {"-11", "-11"}, {"-10", "-10"},
    {"-9", "-9"},   {"-8", "-8"},   {"-7", "-7"},   {"-6", "-6"},   {"-5", "-5"},   {"-4", "-4"},   {"-3", "-3"},
    {"-2", "-2"},   {"-1", "-1"},   {"0", "0"},     {"1", "1"},     {"2", "2"},     {"3", "3"},     {"4", "4"},
    {"5", "5"},     {"6", "6"},     {"7", "7"},     {"8", "8"},     {"9", "9"},     {"10", "10"},   {"11", "11"},
    {"12", "12"},   {"13", "13"},   {"14", "14"},   {"15", "15"},   {"16", "16"},   {"17", "17"},   {"18", "18"},
    {"19", "19"},   {"20", "20"},   {"21", "21"},   {"22", "22"},   {"23", "23"},   {"24", "24"},   {"25", "25"},
    {"26", "26"},   {"27", "27"},   {"28", "28"},   {"29", "29"},   {"30", "30"}},
   "0"},
  {"duckstation_Display.LineStartOffset",
   "Display Line Start Offset",
   "Pads or crops off lines from the top of the displayed image.",
   {{"-30", "-30"}, {"-29", "-29"}, {"-28", "-28"}, {"-27", "-27"}, {"-26", "-26"}, {"-25", "-25"}, {"-24", "-24"},
    {"-23", "-23"}, {"-22", "-22"}, {"-21", "-21"}, {"-20", "-20"}, {"-19", "-19"}, {"-18", "-18"}, {"-17", "-17"},
    {"-16", "-16"}, {"-15", "-15"}, {"-14", "-14"}, {"-13", "-13"}, {"-12", "-12"}, {"-11", "-11"}, {"-10", "-10"},
    {"-9", "-9"},   {"-8", "-8"},   {"-7", "-7"},   {"-6", "-6"},   {"-5", "-5"},   {"-4", "-4"},   {"-3", "-3"},
    {"-2", "-2"},   {"-1", "-1"},   {"0", "0"},     {"1", "1"},     {"2", "2"},     {"3", "3"},     {"4", "4"},
    {"5", "5"},     {"6", "6"},     {"7", "7"},     {"8", "8"},     {"9", "9"},     {"10", "10"},   {"11", "11"},
    {"12", "12"},   {"13", "13"},   {"14", "14"},   {"15", "15"},   {"16", "16"},   {"17", "17"},   {"18", "18"},
    {"19", "19"},   {"20", "20"},   {"21", "21"},   {"22", "22"},   {"23", "23"},   {"24", "24"},   {"25", "25"},
    {"26", "26"},   {"27", "27"},   {"28", "28"},   {"29", "29"},   {"30", "30"}},
   "0"},
  {"duckstation_Display.LineEndOffset",
   "Display Line End Offset",
   "Pads or crops off lines from the bottom of the displayed image.",
   {{"-30", "-30"}, {"-29", "-29"}, {"-28", "-28"}, {"-27", "-27"}, {"-26", "-26"}, {"-25", "-25"}, {"-24", "-24"},
    {"-23", "-23"}, {"-22", "-22"}, {"-21", "-21"}, {"-20", "-20"}, {"-19", "-19"}, {"-18", "-18"}, {"-17", "-17"},
    {"-16", "-16"}, {"-15", "-15"}, {"-14", "-14"}, {"-13", "-13"}, {"-12", "-12"}, {"-11", "-11"}, {"-10", "-10"},
    {"-9", "-9"},   {"-8", "-8"},   {"-7", "-7"},   {"-6", "-6"},   {"-5", "-5"},   {"-4", "-4"},   {"-3", "-3"},
    {"-2", "-2"},   {"-1", "-1"},   {"0", "0"},     {"1", "1"},     {"2", "2"},     {"3", "3"},     {"4", "4"},
    {"5", "5"},     {"6", "6"},     {"7", "7"},     {"8", "8"},     {"9", "9"},     {"10", "10"},   {"11", "11"},
    {"12", "12"},   {"13", "13"},   {"14", "14"},   {"15", "15"},   {"16", "16"},   {"17", "17"},   {"18", "18"},
    {"19", "19"},   {"20", "20"},   {"21", "21"},   {"22", "22"},   {"23", "23"},   {"24", "24"},   {"25", "25"},
    {"26", "26"},   {"27", "27"},   {"28", "28"},   {"29", "29"},   {"30", "30"}},
   "0"},
  {"duckstation_GPU.PGXPPreserveProjFP",
   "PGXP Preserve Projection Precision",
   "Enables additional precision for PGXP. May improve visuals in some games but break others.",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_GPU.PGXPTolerance",
   "PGXP Geometry Tolerance",
   "Ignores precise positions if the difference exceeds this threshold.",
   {
     {"-1.0", "None"},        {"0.5", "0.5 pixels"}, {"1.0", "1.0 pixels"}, {"1.5", "1.5 pixels"},
     {"2.0", "2.0 pixels"},   {"2.5", "2.5 pixels"}, {"3.0", "3.0 pixels"}, {"3.5", "3.5 pixels"},
     {"4.0", "4.0 pixels"},   {"4.5", "4.5 pixels"}, {"5.0", "5.0 pixels"}, {"5.5", "5.5 pixels"},
     {"6.0", "6.0 pixels"},   {"6.5", "6.5 pixels"}, {"7.0", "7.0 pixels"}, {"7.5", "7.5 pixels"},
     {"8.0", "8.0 pixels"},   {"8.5", "8.5 pixels"}, {"9.0", "9.0 pixels"}, {"9.5", "9.0 pixels"},
     {"10.0", "10.0 pixels"},

   },
   "-1.0"},
  {"duckstation_Main.RunaheadFrameCount",
   "Internal Run-Ahead",
   "Simulates the system ahead of time and rolls back/replays to reduce input lag. Has very high system "
   "requirements and forces CPU Execution Mode to Interpreter.",
   {{"0", "0 Frames (Disabled)"},
    {"1", "1 Frame"},
    {"2", "2 Frames"},
    {"3", "3 Frames"},
    {"4", "4 Frames"},
    {"5", "5 Frames"},
    {"6", "6 Frames"},
    {"7", "7 Frames"},
    {"8", "8 Frames"},
    {"9", "9 Frames"},
    {"10", "10 Frames"}},
   "0"},
  {"duckstation_HLE.Enable",
   "Enable HLE bios",
   "Enable HLE bios",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {"duckstation_HLE.LoadBIOS",
   "Load HLE bios for test purpose",
   "Load HLE bios for test purpose",
   {{"true", "Enabled"}, {"false", "Disabled"}},
   "false"},
  {},
}};

bool LibretroHostInterface::SetCoreOptions()
{
  unsigned options_version = 0;
  if (g_retro_environment_callback(RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION, &options_version) &&
      options_version >= 1)
  {
    return g_retro_environment_callback(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, &s_option_definitions);
  }

  // use legacy options struct, which sucks. do we need to?
  return false;
}

bool LibretroHostInterface::HasCoreVariablesChanged()
{
  bool changed = false;
  return (g_retro_environment_callback(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &changed) && changed);
}

std::string LibretroHostInterface::GetBIOSDirectory()
{
  // Assume BIOS files are located in system directory.
  const char* system_directory = nullptr;
  if (!g_retro_environment_callback(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_directory) || !system_directory)
    return GetProgramDirectoryRelativePath("system");
  else
    return system_directory;
}

std::unique_ptr<ByteStream> LibretroHostInterface::OpenPackageFile(const char* path, u32 flags)
{
  Log_ErrorPrintf("Ignoring request for package file '%s'", path);
  return {};
}

void LibretroHostInterface::LoadSettings(SettingsInterface& si)
{
  HostInterface::LoadSettings(si);

  // turn percentage into fraction for overclock
  const u32 overclock_percent = static_cast<u32>(std::max(si.GetIntValue("CPU", "Overclock", 100), 1));
  Settings::CPUOverclockPercentToFraction(overclock_percent, &g_settings.cpu_overclock_numerator,
                                          &g_settings.cpu_overclock_denominator);
  g_settings.cpu_overclock_enable = (overclock_percent != 100);
  g_settings.UpdateOverclockActive();

  // convert msaa settings
  const std::string msaa = si.GetStringValue("GPU", "MSAA", "1");
  g_settings.gpu_multisamples = StringUtil::FromChars<u32>(msaa).value_or(1);
  g_settings.gpu_per_sample_shading = StringUtil::EndsWith(msaa, "-ssaa");

  // Ensure we don't use the standalone memcard directory in shared mode.
  for (u32 i = 0; i < NUM_CONTROLLER_AND_CARD_PORTS; i++)
    g_settings.memory_card_paths[i] = GetSharedMemoryCardPath(i);

  // Set controllers
  g_settings.controller_types = s_controller_types;
}

std::vector<std::string> LibretroHostInterface::GetSettingStringList(const char* section, const char* key)
{
  return {};
}

void LibretroHostInterface::retro_set_controller_port_device(unsigned port, unsigned device)
{
    if (port >= s_controller_types.size())
        return;

    const auto& code = System::GetRunningCode();
    if (isAnalogOnlyGame(code) || isAnalogPreferedGame(code)) {
        auto device_ = (device == RETRO_DEVICE_ANALOG) ? ControllerType::AnalogController : ControllerType::DigitalController;
        s_controller_types[port] = device_;
        UpdateSettings();
        Log_InfoPrintf("New controller setting (%s) for port %d",
                g_settings.controller_types[port] == ControllerType::AnalogController ? "analog" : "digital", port);
    } else {
        Log_ErrorPrintf("retro_set_controller_port_device not an analog game (%s)", code.c_str());
    }
}

void LibretroHostInterface::UpdateSettings()
{
  Settings old_settings(std::move(g_settings));
  LibretroSettingsInterface si;
  LoadSettings(si);
  ApplyGameSettings();
  FixIncompatibleSettings(false);

  if (System::IsValid())
  {
    if (g_settings.gpu_resolution_scale != old_settings.gpu_resolution_scale &&
        g_settings.gpu_renderer != GPURenderer::Software)
    {
      ReportMessage("Resolution changed, updating system AV info...");

      UpdateSystemAVInfo(true);

      if (!g_settings.IsUsingSoftwareRenderer())
      {
        if (!m_hw_render_callback_valid)
          RequestHardwareRendererContext();
        else if (!m_using_hardware_renderer)
          SwitchToHardwareRenderer();
      }

      // Don't let the base class mess with the GPU.
      old_settings.gpu_resolution_scale = g_settings.gpu_resolution_scale;
    }

    if (g_settings.gpu_renderer != old_settings.gpu_renderer)
    {
      ReportFormattedMessage("Switch to %s renderer pending, please restart the core to apply.",
                             Settings::GetRendererDisplayName(g_settings.gpu_renderer));
      g_settings.gpu_renderer = old_settings.gpu_renderer;
    }
  }

  CheckForSettingsChanges(old_settings);
}

void LibretroHostInterface::CheckForSettingsChanges(const Settings& old_settings)
{
  HostInterface::CheckForSettingsChanges(old_settings);

  if (g_settings.display_aspect_ratio != old_settings.display_aspect_ratio)
    UpdateGeometry();

  if (g_settings.log_level != old_settings.log_level)
    UpdateLogging();
}

void LibretroHostInterface::OnRunningGameChanged(const std::string& path, CDImage* image, const std::string& game_code,
                                                 const std::string& game_title)
{
  Log_InfoPrintf("Running game changed: %s (%s)", System::GetRunningCode().c_str(), System::GetRunningTitle().c_str());
  if (UpdateGameSettings())
    UpdateSettings();
}

void LibretroHostInterface::InitRumbleInterface()
{
  m_rumble_interface_valid = g_retro_environment_callback(RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE, &m_rumble_interface);
}

void LibretroHostInterface::UpdateControllers()
{
  g_retro_input_poll_callback();

  for (u32 i = 0; i < NUM_CONTROLLER_AND_CARD_PORTS; i++)
  {
    switch (g_settings.controller_types[i])
    {
      case ControllerType::None:
        break;

      case ControllerType::DigitalController:
        UpdateControllersDigitalController(i);
        break;

      case ControllerType::AnalogController:
        UpdateControllersAnalogController(i);
        break;

      default:
        ReportFormattedError("Unhandled controller type '%s'.",
                             Settings::GetControllerTypeDisplayName(g_settings.controller_types[i]));
        break;
    }
  }
}

void LibretroHostInterface::UpdateControllersDigitalController(u32 index)
{
  DigitalController* controller = static_cast<DigitalController*>(System::GetController(index));
  DebugAssert(controller);

  static constexpr std::array<std::pair<DigitalController::Button, u32>, 14> mapping = {
    {{DigitalController::Button::Left, RETRO_DEVICE_ID_JOYPAD_LEFT},
     {DigitalController::Button::Right, RETRO_DEVICE_ID_JOYPAD_RIGHT},
     {DigitalController::Button::Up, RETRO_DEVICE_ID_JOYPAD_UP},
     {DigitalController::Button::Down, RETRO_DEVICE_ID_JOYPAD_DOWN},
     {DigitalController::Button::Circle, RETRO_DEVICE_ID_JOYPAD_A},
     {DigitalController::Button::Cross, RETRO_DEVICE_ID_JOYPAD_B},
     {DigitalController::Button::Triangle, RETRO_DEVICE_ID_JOYPAD_X},
     {DigitalController::Button::Square, RETRO_DEVICE_ID_JOYPAD_Y},
     {DigitalController::Button::Start, RETRO_DEVICE_ID_JOYPAD_START},
     {DigitalController::Button::Select, RETRO_DEVICE_ID_JOYPAD_SELECT},
     {DigitalController::Button::L1, RETRO_DEVICE_ID_JOYPAD_L},
     {DigitalController::Button::L2, RETRO_DEVICE_ID_JOYPAD_L2},
     {DigitalController::Button::R1, RETRO_DEVICE_ID_JOYPAD_R},
     {DigitalController::Button::R2, RETRO_DEVICE_ID_JOYPAD_R2}}};

  if (m_supports_input_bitmasks)
  {
    const u16 active = g_retro_input_state_callback(index, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_MASK);
    for (const auto& it : mapping)
      controller->SetButtonState(it.first, (active & (static_cast<u16>(1u) << it.second)) != 0u);
  }
  else
  {
    for (const auto& it : mapping)
    {
      const int16_t state = g_retro_input_state_callback(index, RETRO_DEVICE_JOYPAD, 0, it.second);
      controller->SetButtonState(it.first, state != 0);
    }
  }
}

void LibretroHostInterface::UpdateControllersAnalogController(u32 index)
{
  AnalogController* controller = static_cast<AnalogController*>(System::GetController(index));
  DebugAssert(controller);

  static constexpr std::array<std::pair<AnalogController::Button, u32>, 16> button_mapping = {
    {{AnalogController::Button::Left, RETRO_DEVICE_ID_JOYPAD_LEFT},
     {AnalogController::Button::Right, RETRO_DEVICE_ID_JOYPAD_RIGHT},
     {AnalogController::Button::Up, RETRO_DEVICE_ID_JOYPAD_UP},
     {AnalogController::Button::Down, RETRO_DEVICE_ID_JOYPAD_DOWN},
     {AnalogController::Button::Circle, RETRO_DEVICE_ID_JOYPAD_A},
     {AnalogController::Button::Cross, RETRO_DEVICE_ID_JOYPAD_B},
     {AnalogController::Button::Triangle, RETRO_DEVICE_ID_JOYPAD_X},
     {AnalogController::Button::Square, RETRO_DEVICE_ID_JOYPAD_Y},
     {AnalogController::Button::Start, RETRO_DEVICE_ID_JOYPAD_START},
     {AnalogController::Button::Select, RETRO_DEVICE_ID_JOYPAD_SELECT},
     {AnalogController::Button::L1, RETRO_DEVICE_ID_JOYPAD_L},
     {AnalogController::Button::L2, RETRO_DEVICE_ID_JOYPAD_L2},
     {AnalogController::Button::L3, RETRO_DEVICE_ID_JOYPAD_L3},
     {AnalogController::Button::R1, RETRO_DEVICE_ID_JOYPAD_R},
     {AnalogController::Button::R2, RETRO_DEVICE_ID_JOYPAD_R2},
     {AnalogController::Button::R3, RETRO_DEVICE_ID_JOYPAD_R3}}};

  static constexpr std::array<std::pair<AnalogController::Axis, std::pair<u32, u32>>, 4> axis_mapping = {
    {{AnalogController::Axis::LeftX, {RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X}},
     {AnalogController::Axis::LeftY, {RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y}},
     {AnalogController::Axis::RightX, {RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X}},
     {AnalogController::Axis::RightY, {RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y}}}};

  if (m_supports_input_bitmasks)
  {
    const u16 active = g_retro_input_state_callback(index, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_MASK);
    for (const auto& it : button_mapping)
      controller->SetButtonState(it.first, (active & (static_cast<u16>(1u) << it.second)) != 0u);
  }
  else
  {
    for (const auto& it : button_mapping)
    {
      const int16_t state = g_retro_input_state_callback(index, RETRO_DEVICE_JOYPAD, 0, it.second);
      controller->SetButtonState(it.first, state != 0);
    }
  }

  for (const auto& it : axis_mapping)
  {
    const int16_t state = g_retro_input_state_callback(index, RETRO_DEVICE_ANALOG, it.second.first, it.second.second);
    controller->SetAxisState(static_cast<s32>(it.first), std::clamp(static_cast<float>(state) / 32767.0f, -1.0f, 1.0f));
  }

  if (m_rumble_interface_valid)
  {
    const u16 strong = static_cast<u16>(static_cast<u32>(controller->GetVibrationMotorStrength(0) * 65535.0f));
    const u16 weak = static_cast<u16>(static_cast<u32>(controller->GetVibrationMotorStrength(1) * 65535.0f));
    m_rumble_interface.set_rumble_state(index, RETRO_RUMBLE_STRONG, strong);
    m_rumble_interface.set_rumble_state(index, RETRO_RUMBLE_WEAK, weak);
  }
}

static std::optional<GPURenderer> RetroHwContextToRenderer(retro_hw_context_type type)
{
  switch (type)
  {
    case RETRO_HW_CONTEXT_OPENGL:
    case RETRO_HW_CONTEXT_OPENGL_CORE:
    case RETRO_HW_CONTEXT_OPENGLES3:
    case RETRO_HW_CONTEXT_OPENGLES_VERSION:
      return GPURenderer::HardwareOpenGL;

    case RETRO_HW_CONTEXT_VULKAN:
      return GPURenderer::HardwareVulkan;

#ifdef WIN32
    case RETRO_HW_CONTEXT_DIRECT3D:
      return GPURenderer::HardwareD3D11;
#endif

    default:
      return std::nullopt;
  }
}

static std::optional<GPURenderer> RenderAPIToRenderer(HostDisplay::RenderAPI api)
{
  switch (api)
  {
    case HostDisplay::RenderAPI::OpenGL:
    case HostDisplay::RenderAPI::OpenGLES:
      return GPURenderer::HardwareOpenGL;

    case HostDisplay::RenderAPI::Vulkan:
      return GPURenderer::HardwareVulkan;

#ifdef WIN32
    case HostDisplay::RenderAPI::D3D11:
      return GPURenderer::HardwareD3D11;
#endif

    default:
      return std::nullopt;
  }
}

bool LibretroHostInterface::RequestHardwareRendererContext()
{
  retro_variable renderer_variable{"duckstation_GPU.Renderer",
                                   Settings::GetRendererName(Settings::DEFAULT_GPU_RENDERER)};
  if (!g_retro_environment_callback(RETRO_ENVIRONMENT_GET_VARIABLE, &renderer_variable) || !renderer_variable.value)
    renderer_variable.value = Settings::GetRendererName(Settings::DEFAULT_GPU_RENDERER);

  GPURenderer renderer = Settings::ParseRendererName(renderer_variable.value).value_or(Settings::DEFAULT_GPU_RENDERER);
  unsigned preferred_renderer = 0;
  g_retro_environment_callback(RETRO_ENVIRONMENT_GET_PREFERRED_HW_RENDER, &preferred_renderer);
  if (std::strcmp(renderer_variable.value, "Auto") == 0)
  {
    std::optional<GPURenderer> preferred_gpu_renderer =
      RetroHwContextToRenderer(static_cast<retro_hw_context_type>(preferred_renderer));
    if (preferred_gpu_renderer.has_value())
      renderer = preferred_gpu_renderer.value();
  }

  Log_InfoPrintf("Renderer = %s", Settings::GetRendererName(renderer));
  if (renderer == GPURenderer::Software)
  {
    m_hw_render_callback_valid = false;
    return false;
  }

  Log_InfoPrintf("Requesting hardware renderer context for %s", Settings::GetRendererName(renderer));

  m_hw_render_callback = {};
  m_hw_render_callback.context_reset = HardwareRendererContextReset;
  m_hw_render_callback.context_destroy = HardwareRendererContextDestroy;

  switch (renderer)
  {
#ifdef WIN32
    case GPURenderer::HardwareD3D11:
      m_hw_render_callback_valid = LibretroD3D11HostDisplay::RequestHardwareRendererContext(&m_hw_render_callback);
      break;
#endif

    case GPURenderer::HardwareVulkan:
      m_hw_render_callback_valid = LibretroVulkanHostDisplay::RequestHardwareRendererContext(&m_hw_render_callback);
      break;

    case GPURenderer::HardwareOpenGL:
    {
      const bool prefer_gles =
        (preferred_renderer == RETRO_HW_CONTEXT_OPENGLES2 || preferred_renderer == RETRO_HW_CONTEXT_OPENGLES_VERSION);
      m_hw_render_callback_valid =
        LibretroOpenGLHostDisplay::RequestHardwareRendererContext(&m_hw_render_callback, prefer_gles);
    }
    break;

    default:
      Log_ErrorPrintf("Unhandled renderer %s", Settings::GetRendererName(renderer));
      m_hw_render_callback_valid = false;
      break;
  }

  return m_hw_render_callback_valid;
}

void LibretroHostInterface::HardwareRendererContextReset()
{
  Log_InfoPrintf("Hardware context reset, type = %u",
                 static_cast<unsigned>(g_libretro_host_interface.m_hw_render_callback.context_type));

  g_libretro_host_interface.m_hw_render_callback_valid = true;
  g_libretro_host_interface.SwitchToHardwareRenderer();
}

void LibretroHostInterface::SwitchToHardwareRenderer()
{
  struct retro_system_av_info avi;
  g_libretro_host_interface.GetSystemAVInfo(&avi, true);

  WindowInfo wi;
  wi.type = WindowInfo::Type::Libretro;
  wi.display_connection = &g_libretro_host_interface.m_hw_render_callback;
  wi.surface_width = avi.geometry.base_width;
  wi.surface_height = avi.geometry.base_height;
  wi.surface_scale = 1.0f;

  // use the existing device if we just resized the window
  std::optional<GPURenderer> renderer;
  std::unique_ptr<HostDisplay> display = std::move(m_hw_render_display);
  if (display)
  {
    Log_InfoPrintf("Using existing hardware display");
    renderer = RenderAPIToRenderer(display->GetRenderAPI());
    if (!display->ChangeRenderWindow(wi) || !display->CreateResources())
    {
      Log_ErrorPrintf("Failed to recreate resources after reinit");
      display->DestroyRenderDevice();
      display.reset();
    }
  }

  if (!display)
  {
    renderer = RetroHwContextToRenderer(m_hw_render_callback.context_type);
    if (!renderer.has_value())
    {
      Log_ErrorPrintf("Unknown context type %u", static_cast<unsigned>(m_hw_render_callback.context_type));
      return;
    }

    switch (renderer.value())
    {
      case GPURenderer::HardwareOpenGL:
        display = std::make_unique<LibretroOpenGLHostDisplay>();
        break;

      case GPURenderer::HardwareVulkan:
        display = std::make_unique<LibretroVulkanHostDisplay>();
        break;

#ifdef WIN32
      case GPURenderer::HardwareD3D11:
        display = std::make_unique<LibretroD3D11HostDisplay>();
        break;
#endif

      default:
        Log_ErrorPrintf("Unhandled renderer '%s'", Settings::GetRendererName(renderer.value()));
        return;
    }
    if (!display || !display->CreateRenderDevice(wi, {}, g_settings.gpu_use_debug_device, false) ||
        !display->InitializeRenderDevice(GetShaderCacheBasePath(), g_settings.gpu_use_debug_device, false))
    {
      Log_ErrorPrintf("Failed to create hardware host display");
      return;
    }
  }

  std::swap(display, g_libretro_host_interface.m_display);
  System::RecreateGPU(renderer.value());
  display->DestroyRenderDevice();
  m_using_hardware_renderer = true;
}

void LibretroHostInterface::HardwareRendererContextDestroy()
{
  Log_InfoPrintf("Hardware context destroyed");

  // switch back to software
  if (g_libretro_host_interface.m_using_hardware_renderer)
    g_libretro_host_interface.SwitchToSoftwareRenderer();

  if (g_libretro_host_interface.m_hw_render_display)
  {
    g_libretro_host_interface.m_hw_render_display->DestroyRenderDevice();
    g_libretro_host_interface.m_hw_render_display.reset();
  }

  g_libretro_host_interface.m_hw_render_callback_valid = false;
}

void LibretroHostInterface::SwitchToSoftwareRenderer()
{
  Log_InfoPrintf("Switching to software renderer");

  // keep the hw renderer around in case we need it later
  // but keep it active until we've recreated the GPU so we can save the state
  std::unique_ptr<HostDisplay> save_display;
  if (m_using_hardware_renderer)
  {
    save_display = std::move(m_display);
    m_using_hardware_renderer = false;
  }

  m_display = std::make_unique<LibretroHostDisplay>();
  System::RecreateGPU(GPURenderer::Software, false);

  if (save_display)
  {
    save_display->DestroyResources();
    m_hw_render_display = std::move(save_display);
  }
}

bool LibretroHostInterface::DiskControlSetEjectState(bool ejected)
{
  if (System::IsShutdown())
    return false;

  if (ejected)
  {
    if (!System::HasMedia())
      return false;

    System::RemoveMedia();
  }
  else
  {
    if (System::HasMedia())
      return false;

    if (P_THIS->m_disk_control_info.has_sub_images)
    {
      if (!System::InsertMedia(P_THIS->m_disk_control_info.sub_images_parent_path.c_str()))
        return false;

      if (!System::SwitchMediaSubImage(P_THIS->m_disk_control_info.image_index))
        return false;
    }
    else if (!System::InsertMedia(P_THIS->m_disk_control_info.image_paths[P_THIS->m_disk_control_info.image_index].c_str()))
      return false;
  }

  return true;
}

bool LibretroHostInterface::DiskControlGetEjectState()
{
  if (System::IsShutdown())
    return false;

  return !System::HasMedia();
}

unsigned LibretroHostInterface::DiskControlGetImageIndex()
{
  return (unsigned)P_THIS->m_disk_control_info.image_index;
}

bool LibretroHostInterface::DiskControlSetImageIndex(unsigned index)
{
  if (System::IsShutdown() ||
      System::HasMedia() ||
      (index >= P_THIS->m_disk_control_info.image_count))
    return false;

  P_THIS->m_disk_control_info.image_index = (u32)index;
  return true;
}

unsigned LibretroHostInterface::DiskControlGetNumImages()
{
  return (unsigned)P_THIS->m_disk_control_info.image_count;
}

bool LibretroHostInterface::DiskControlReplaceImageIndex(unsigned index, const retro_game_info* info)
{
#ifdef _MSC_VER
#define CASE_COMPARE _stricmp
#else
#define CASE_COMPARE strcasecmp
#endif

  if (System::IsShutdown() ||
      System::HasMedia() ||
      (index >= P_THIS->m_disk_control_info.image_count))
    return false;

  /* Multi-image content cannot be modified */
  if (P_THIS->m_disk_control_info.has_sub_images)
    return false;

  if (!info)
  {
    /* Remove specified image */
    P_THIS->m_disk_control_info.image_count--;

    if (index < P_THIS->m_disk_control_info.image_index)
      P_THIS->m_disk_control_info.image_index--;

    P_THIS->m_disk_control_info.image_paths.erase(
        P_THIS->m_disk_control_info.image_paths.begin() + index);
    P_THIS->m_disk_control_info.image_labels.erase(
        P_THIS->m_disk_control_info.image_labels.begin() + index);
    return true;
  }

  if (!info->path)
    return false;

  const char *extension = std::strrchr(info->path, '.');
  if (!extension)
    return false;

  /* We cannot 'insert' an M3U file
   * > New image must be 'single disk' content */
  if (CASE_COMPARE(extension, ".m3u") == 0)
    return false;

  const std::string_view image_label = FileSystem::GetFileTitleFromPath(info->path);
  if (image_label.empty())
    return false;

  P_THIS->m_disk_control_info.image_paths[index]  = info->path;
  P_THIS->m_disk_control_info.image_labels[index] = std::string(image_label);
  return true;
}

bool LibretroHostInterface::DiskControlAddImageIndex()
{
  if (System::IsShutdown())
    return false;

  /* Multi-image content cannot be modified */
  if (P_THIS->m_disk_control_info.has_sub_images)
    return false;

  P_THIS->m_disk_control_info.image_count++;
  P_THIS->m_disk_control_info.image_paths.push_back("");
  P_THIS->m_disk_control_info.image_labels.push_back("");
  return true;
}

bool LibretroHostInterface::DiskControlSetInitialImage(unsigned index, const char* path)
{
  /* Note: 'path' is ignored, since we cannot
   * determine the actual set path until after
   * content is loaded by the core emulation
   * code (at which point it is too late to
   * compare it with the value supplied here) */
  P_THIS->m_disk_control_info.initial_image_index = index;
  return true;
}

bool LibretroHostInterface::DiskControlGetImagePath(unsigned index, char* path, size_t len)
{
  if ((index >= P_THIS->m_disk_control_info.image_count) ||
      (index >= P_THIS->m_disk_control_info.image_paths.size()) ||
      P_THIS->m_disk_control_info.image_paths[index].empty())
    return false;

  StringUtil::Strlcpy(path, P_THIS->m_disk_control_info.image_paths[index].c_str(), len);
  return true;
}

bool LibretroHostInterface::DiskControlGetImageLabel(unsigned index, char* label, size_t len)
{
  if ((index >= P_THIS->m_disk_control_info.image_count) ||
      (index >= P_THIS->m_disk_control_info.image_labels.size()) ||
      P_THIS->m_disk_control_info.image_labels[index].empty())
    return false;

  StringUtil::Strlcpy(label, P_THIS->m_disk_control_info.image_labels[index].c_str(), len);
  return true;
}

void LibretroHostInterface::InitDiskControlInterface()
{
  unsigned version = 0;
  if (g_retro_environment_callback(RETRO_ENVIRONMENT_GET_DISK_CONTROL_INTERFACE_VERSION, &version) && version >= 1)
  {
    retro_disk_control_ext_callback ext_cb = {
      &LibretroHostInterface::DiskControlSetEjectState, &LibretroHostInterface::DiskControlGetEjectState,
      &LibretroHostInterface::DiskControlGetImageIndex, &LibretroHostInterface::DiskControlSetImageIndex,
      &LibretroHostInterface::DiskControlGetNumImages,  &LibretroHostInterface::DiskControlReplaceImageIndex,
      &LibretroHostInterface::DiskControlAddImageIndex, &LibretroHostInterface::DiskControlSetInitialImage,
      &LibretroHostInterface::DiskControlGetImagePath,  &LibretroHostInterface::DiskControlGetImageLabel};
    if (g_retro_environment_callback(RETRO_ENVIRONMENT_SET_DISK_CONTROL_EXT_INTERFACE, &ext_cb))
      return;
  }

  retro_disk_control_callback cb = {
    &LibretroHostInterface::DiskControlSetEjectState, &LibretroHostInterface::DiskControlGetEjectState,
    &LibretroHostInterface::DiskControlGetImageIndex, &LibretroHostInterface::DiskControlSetImageIndex,
    &LibretroHostInterface::DiskControlGetNumImages,  &LibretroHostInterface::DiskControlReplaceImageIndex,
    &LibretroHostInterface::DiskControlAddImageIndex};
  if (!g_retro_environment_callback(RETRO_ENVIRONMENT_SET_DISK_CONTROL_INTERFACE, &cb))
    Log_WarningPrint("Failed to set disk control interface");
}
