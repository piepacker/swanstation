#include "gpu_sw_backend.h"
#include "common/assert.h"
#include "common/log.h"
#include "gpu_sw_backend.h"
#include "host_display.h"
#include "system.h"
#include <algorithm>
Log_SetChannel(GPU_SW_Backend);

#define SCALE_ALL_VERTEX 1
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244) // warning C4324: 'GPUBackend': structure was padded due to alignment specifier
#endif

GPU_SW_Backend::GPU_SW_Backend() : GPUBackend()
{
  m_upram.fill(0);
  m_upram_ptr = m_upram.data();
}

GPU_SW_Backend::~GPU_SW_Backend() = default;

bool GPU_SW_Backend::Initialize()
{
  return GPUBackend::Initialize();
}

void GPU_SW_Backend::Reset(bool clear_vram)
{
  GPUBackend::Reset(clear_vram);

  if (clear_vram)
    m_upram.fill(0);
}

void GPU_SW_Backend::DrawPolygon(const GPUBackendDrawPolygonCommand* cmd)
{
  const GPURenderCommand rc{cmd->rc.bits};
  const bool dithering_enable = rc.IsDitheringEnabled() && cmd->draw_mode.dither_enable;

  const DrawTriangleFunction DrawFunction = GetDrawTriangleFunction(
    rc.shading_enable, rc.texture_enable, rc.raw_texture_enable, rc.transparency_enable, dithering_enable);

  (this->*DrawFunction)(cmd, &cmd->vertices[0], &cmd->vertices[1], &cmd->vertices[2]);
  if (rc.quad_polygon)
    (this->*DrawFunction)(cmd, &cmd->vertices[2], &cmd->vertices[1], &cmd->vertices[3]);
}

void GPU_SW_Backend::DrawRectangle(const GPUBackendDrawRectangleCommand* cmd)
{
  const GPURenderCommand rc{cmd->rc.bits};

  const DrawRectangleFunction DrawFunction =
    GetDrawRectangleFunction(rc.texture_enable, rc.raw_texture_enable, rc.transparency_enable);

  (this->*DrawFunction)(cmd);
}

void GPU_SW_Backend::DrawLine(const GPUBackendDrawLineCommand* cmd)
{
  const DrawLineFunction DrawFunction =
    GetDrawLineFunction(cmd->rc.shading_enable, cmd->rc.transparency_enable, cmd->IsDitheringEnabled());

  for (u16 i = 1; i < cmd->num_vertices; i++)
    (this->*DrawFunction)(cmd, &cmd->vertices[i - 1], &cmd->vertices[i]);
}

constexpr GPU_SW_Backend::DitherLUT GPU_SW_Backend::ComputeDitherLUT()
{
  DitherLUT lut = {};
  for (u32 i = 0; i < DITHER_MATRIX_SIZE; i++)
  {
    for (u32 j = 0; j < DITHER_MATRIX_SIZE; j++)
    {
      for (u32 value = 0; value < DITHER_LUT_SIZE; value++)
      {
        const s32 dithered_value = (static_cast<s32>(value) + DITHER_MATRIX[i][j]) >> 3;
        lut[i][j][value] = static_cast<u8>((dithered_value < 0) ? 0 : ((dithered_value > 31) ? 31 : dithered_value));
      }
    }
  }
  return lut;
}

static constexpr GPU_SW_Backend::DitherLUT s_dither_lut = GPU_SW_Backend::ComputeDitherLUT();


s32 ApplyTextureWindow(const GPUBackendDrawCommand* cmd, s32 coords)
{
  return (coords & cmd->window.and_x) | cmd->window.or_x;
}

s32 ApplyUpscaledTextureWindow(const GPUBackendDrawCommand* cmd, s32 coords)
{
  auto native_coords = coords / RESOLUTION_SCALE;
  auto coords_offset = coords % RESOLUTION_SCALE;
  return (ApplyTextureWindow(cmd, native_coords) * RESOLUTION_SCALE) + coords_offset;
}

s32 FloatToIntegerCoord(float coord)
{
  // With the vertex offset applied at 1x resolution scale, we want to round the texture coordinates.
  // Floor them otherwise, as it currently breaks when upscaling as the vertex offset is not applied.
  return (RESOLUTION_SCALE == 1u) ? roundf(coord) : floorf(coord);
}

template<bool texture_enable, bool raw_texture_enable, bool transparency_enable, bool dithering_enable>
void ALWAYS_INLINE_RELEASE GPU_SW_Backend::ShadePixel(const GPUBackendDrawCommand* cmd, s32 x, s32 y, u8 color_r,
                                                      u8 color_g, u8 color_b, float texcoord_x_f32, float texcoord_y_f32)
{
  VRAMPixel color;
  bool transparent;
  if constexpr (texture_enable)
  {
    // Apply texture window
    // TODO: Precompute the second half
    //float texcoord_x = (texcoord_x & cmd->window.and_x) | cmd->window.or_x;
    //float texcoord_y = (texcoord_y & cmd->window.and_y) | cmd->window.or_y;

    //auto texcoord_x = ApplyUpscaledTextureWindow(cmd, FloatToIntegerCoord(texcoord_x_f32));
    //auto texcoord_y = ApplyUpscaledTextureWindow(cmd, FloatToIntegerCoord(texcoord_y_f32));

    auto texcoord_x = ApplyTextureWindow(cmd, FloatToIntegerCoord(texcoord_x_f32));
    auto texcoord_y = ApplyTextureWindow(cmd, FloatToIntegerCoord(texcoord_y_f32));

    VRAMPixel texture_color;
    switch (cmd->draw_mode.texture_mode)
    {
      case GPUTextureMode::Palette4Bit:
      {
        const u16 palette_value =
          GetPixel((cmd->draw_mode.GetTexturePageBaseX() + (texcoord_x / 4)) % VRAM_WIDTH,
                   (cmd->draw_mode.GetTexturePageBaseY() + (texcoord_y)) % VRAM_HEIGHT);
        const u16 palette_index = (palette_value >> ((texcoord_x % 4) * 4)) & 0x0Fu;

        texture_color.bits =
          GetPixel((cmd->palette.GetXBase() + (palette_index)) % VRAM_WIDTH, cmd->palette.GetYBase());
      }
      break;

      case GPUTextureMode::Palette8Bit:
      {
        const u16 palette_value =
          GetPixel((cmd->draw_mode.GetTexturePageBaseX() + (texcoord_x / 2)) % VRAM_WIDTH,
                   (cmd->draw_mode.GetTexturePageBaseY() + (texcoord_y)) % VRAM_HEIGHT);
        const u16 palette_index = (palette_value >> ((texcoord_x % 2) * 8)) & 0xFFu;
        texture_color.bits =
          GetPixel((cmd->palette.GetXBase() + (palette_index)) % VRAM_WIDTH, cmd->palette.GetYBase());
      }
      break;

      default:
      {
        texture_color.bits = GetPixel((cmd->draw_mode.GetTexturePageBaseX() + (texcoord_x)) % VRAM_WIDTH,
                                      (cmd->draw_mode.GetTexturePageBaseY() + (texcoord_y)) % VRAM_HEIGHT);
      }
      break;
    }

    if (texture_color.bits == 0)
      return;

    transparent = texture_color.c;

    if constexpr (raw_texture_enable)
    {
      color.bits = texture_color.bits;
    }
    else
    {
      const u32 dither_y = (dithering_enable) ? (y & 3u) : 2u;
      const u32 dither_x = (dithering_enable) ? (x & 3u) : 3u;

      color.bits = (ZeroExtend16(s_dither_lut[dither_y][dither_x][(u16(texture_color.r) * u16(color_r)) >> 4]) << 0) |
                   (ZeroExtend16(s_dither_lut[dither_y][dither_x][(u16(texture_color.g) * u16(color_g)) >> 4]) << 5) |
                   (ZeroExtend16(s_dither_lut[dither_y][dither_x][(u16(texture_color.b) * u16(color_b)) >> 4]) << 10) |
                   (texture_color.bits & 0x8000u);
    }
  }
  else
  {
    transparent = true;

    const u32 dither_y = (dithering_enable) ? (y & 3u) : 2u;
    const u32 dither_x = (dithering_enable) ? (x & 3u) : 3u;

    color.bits = (ZeroExtend16(s_dither_lut[dither_y][dither_x][color_r]) << 0) |
                 (ZeroExtend16(s_dither_lut[dither_y][dither_x][color_g]) << 5) |
                 (ZeroExtend16(s_dither_lut[dither_y][dither_x][color_b]) << 10);
  }

  //const VRAMPixel bg_color{GetPixel(x, y)};
  const VRAMPixel bg_color { UPRAM_ACCESSOR[VRAM_UPRENDER_SIZE_X * y + x] };

  if constexpr (transparency_enable)
  {
    if (transparent)
    {
#define BLEND_AVERAGE(bg, fg) Truncate8(std::min<u32>((ZeroExtend32(bg) / 2) + (ZeroExtend32(fg) / 2), 0x1F))
#define BLEND_ADD(bg, fg) Truncate8(std::min<u32>(ZeroExtend32(bg) + ZeroExtend32(fg), 0x1F))
#define BLEND_SUBTRACT(bg, fg) Truncate8((bg > fg) ? ((bg) - (fg)) : 0)
#define BLEND_QUARTER(bg, fg) Truncate8(std::min<u32>(ZeroExtend32(bg) + ZeroExtend32(fg / 4), 0x1F))

#define BLEND_RGB(func)                                                                                                \
  color.Set(func(bg_color.r.GetValue(), color.r.GetValue()), func(bg_color.g.GetValue(), color.g.GetValue()),          \
            func(bg_color.b.GetValue(), color.b.GetValue()), color.c.GetValue())

      switch (cmd->draw_mode.transparency_mode)
      {
        case GPUTransparencyMode::HalfBackgroundPlusHalfForeground:
          BLEND_RGB(BLEND_AVERAGE);
          break;
        case GPUTransparencyMode::BackgroundPlusForeground:
          BLEND_RGB(BLEND_ADD);
          break;
        case GPUTransparencyMode::BackgroundMinusForeground:
          BLEND_RGB(BLEND_SUBTRACT);
          break;
        case GPUTransparencyMode::BackgroundPlusQuarterForeground:
          BLEND_RGB(BLEND_QUARTER);
          break;
        default:
          break;
      }

#undef BLEND_RGB

#undef BLEND_QUARTER
#undef BLEND_SUBTRACT
#undef BLEND_ADD
#undef BLEND_AVERAGE
    }
  }
  else
  {
    UNREFERENCED_VARIABLE(transparent);
  }

  const u16 mask_and = cmd->params.GetMaskAND();
  if ((bg_color.bits & mask_and) != 0)
    return;

  UPRAM_ACCESSOR[VRAM_UPRENDER_SIZE_X * y + x] = (color.bits | cmd->params.GetMaskOR());
  //SetPixel(static_cast<u32>(x), static_cast<u32>(y), color.bits | cmd->params.GetMaskOR());
}

template<bool texture_enable, bool raw_texture_enable, bool transparency_enable>
void GPU_SW_Backend::DrawRectangle(const GPUBackendDrawRectangleCommand* cmd)
{
  const s32 origin_x = cmd->x;
  const s32 origin_y = cmd->y;
  const auto [r, g, b] = UnpackColorRGB24(cmd->color);
  const auto [origin_texcoord_x, origin_texcoord_y] = UnpackTexcoord(cmd->texcoord);

  auto origin_x_up = origin_x * RESOLUTION_SCALE;
  auto origin_y_up = origin_y * RESOLUTION_SCALE;

  auto size_x_up = cmd->width  * RESOLUTION_SCALE;
  auto size_y_up = cmd->height * RESOLUTION_SCALE;

  for (int offset_y = 0; offset_y < size_y_up; offset_y++)
  {
    const s32 y_up = origin_y_up + static_cast<s32>(offset_y);
    if (y_up < static_cast<s32>(m_drawing_area.top * RESOLUTION_SCALE) || y_up > static_cast<s32>(m_drawing_area.bottom * RESOLUTION_SCALE) ||
        (cmd->params.interlaced_rendering && cmd->params.active_line_lsb == (Truncate8(static_cast<u32>(y_up)) & 1u)))
    {
      continue;
    }

    const u8 texcoord_y = Truncate8(ZeroExtend32(origin_texcoord_y) + (offset_y / RESOLUTION_SCALE));

    for (int offset_x = 0; offset_x < size_x_up; offset_x++)
    {
      const s32 x_up = origin_x_up + static_cast<s32>(offset_x);
      if (x_up < static_cast<s32>(m_drawing_area.left * RESOLUTION_SCALE) || x_up > static_cast<s32>(m_drawing_area.right * RESOLUTION_SCALE))
        continue;

      // TODO: sub-pixel texture sampling?
      // Not sure it matters unless we're using tex replacements, as PSX was very likely using 1:1 scale textures
      // for rectangle draws.
      const u8 texcoord_x = Truncate8(ZeroExtend32(origin_texcoord_x) + (offset_x / RESOLUTION_SCALE));

      ShadePixel<texture_enable, raw_texture_enable, transparency_enable, false>(
        cmd, static_cast<u32>(x_up), static_cast<u32>(y_up), r, g, b, texcoord_x, texcoord_y);
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// Polygon and line rasterization ported from Mednafen
//////////////////////////////////////////////////////////////////////////

#define COORD_FBS 12
#define COORD_MF_INT(n) ((n) << COORD_FBS)
#define COORD_POST_PADDING 10

static ALWAYS_INLINE_RELEASE s64 MakePolyXFP(s32 x)
{
  return ((u64)x << 32) + ((1ULL << 32) - (1 << 11));
}

static ALWAYS_INLINE_RELEASE s64 MakePolyXFPStep(s32 dx, s32 dy)
{
  s64 ret;
  s64 dx_ex = (u64)dx << 32;

  if (dx_ex < 0)
    dx_ex -= dy - 1;

  if (dx_ex > 0)
    dx_ex += dy - 1;

  ret = dx_ex / dy;

  return (ret);
}

static ALWAYS_INLINE_RELEASE s32 GetPolyXFP_Int(s64 xfp)
{
  return (xfp >> 32);
}

template<bool shading_enable, bool texture_enable>
bool ALWAYS_INLINE_RELEASE GPU_SW_Backend::CalcIDeltas(i_deltas& idl, const GPUBackendDrawPolygonCommand::Vertex* A,
                                                       const GPUBackendDrawPolygonCommand::Vertex* B,
                                                       const GPUBackendDrawPolygonCommand::Vertex* C)
{
#define CALCIS(x, y) (((B->x - A->x) * (C->y - B->y)) - ((C->x - B->x) * (B->y - A->y)))

  s32 denom = CALCIS(x, y);

  if (!denom)
    return false;

  if constexpr (shading_enable)
  {
    idl.dr_dx = (u32)(CALCIS(r, y) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;
    idl.dr_dy = (u32)(CALCIS(x, r) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;

    idl.dg_dx = (u32)(CALCIS(g, y) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;
    idl.dg_dy = (u32)(CALCIS(x, g) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;

    idl.db_dx = (u32)(CALCIS(b, y) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;
    idl.db_dy = (u32)(CALCIS(x, b) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;
  }

  if constexpr (texture_enable)
  {
    idl.du_dx = (u32)(CALCIS(u, y) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;
    idl.du_dy = (u32)(CALCIS(x, u) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;

    idl.dv_dx = (u32)(CALCIS(v, y) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;
    idl.dv_dy = (u32)(CALCIS(x, v) * (1 << COORD_FBS) / denom) << COORD_POST_PADDING;
  }

  return true;

#undef CALCIS
}

template<bool shading_enable, bool texture_enable, typename I_GROUP>
void ALWAYS_INLINE_RELEASE GPU_SW_Backend::AddIDeltas_DX(I_GROUP& ig, const i_deltas& idl, float count /*= 1*/)
{
  if constexpr (shading_enable)
  {
    ig.r += idl.dr_dx * count;
    ig.g += idl.dg_dx * count;
    ig.b += idl.db_dx * count;
  }

  if constexpr (texture_enable)
  {
    ig.u += idl.du_dx * count;
    ig.v += idl.dv_dx * count;
  }
}

template<bool shading_enable, bool texture_enable, typename I_GROUP>
void ALWAYS_INLINE_RELEASE GPU_SW_Backend::AddIDeltas_DY(I_GROUP& ig, const i_deltas& idl, float count /*= 1*/)
{
  if constexpr (shading_enable)
  {
    ig.r += idl.dr_dy * count;
    ig.g += idl.dg_dy * count;
    ig.b += idl.db_dy * count;
  }

  if constexpr (texture_enable)
  {
    ig.u += idl.du_dy * count;
    ig.v += idl.dv_dy * count;
  }
}

struct i_group_float
{
  float u, v;
  float r, g, b;
};

#define USE_FLOAT_STEP 0
#define USE_INT_STEP   1

template<bool shading_enable, bool texture_enable, bool raw_texture_enable, bool transparency_enable,
         bool dithering_enable>
void GPU_SW_Backend::DrawSpan(const GPUBackendDrawPolygonCommand* cmd, s32 y_up, s32 x_start_up, s32 x_bound_up, i_group igi,
                              const i_deltas& idl)
{
  auto y_native       = y_up       / RESOLUTION_SCALE;
  auto x_start_native = x_start_up / RESOLUTION_SCALE;
  auto x_bound_native = x_bound_up / RESOLUTION_SCALE;

  if (cmd->params.interlaced_rendering && cmd->params.active_line_lsb == (y_up & 1u))
    return;

  s32 x_ig_adjust = x_start_up;
  s32 w_native    = x_bound_native - x_start_native;
  s32 w_up        = x_bound_up     - x_start_up;
  s32 x_native    = SignExtendN<11, s32>(x_start_native);
  s32 x_up        = SignExtendN<11 + RESOLUTION_SHIFT, s32>(x_start_up);

  if (x_up < static_cast<s32>(m_drawing_area.left * RESOLUTION_SCALE))
  {
    s32 delta_up     = static_cast<s32>(m_drawing_area.left * RESOLUTION_SCALE) - x_up;
    x_ig_adjust += delta_up;
    x_up     += delta_up;
    w_up     -= delta_up;
  }

  if ((x_up + w_up) > (static_cast<s32>(m_drawing_area.right * RESOLUTION_SCALE) + 2))
  {
    w_up = static_cast<s32>(m_drawing_area.right * RESOLUTION_SCALE) + 2 - x_up;
  }

  if (w_up <= 0)
    return;

#if 0
  if (x_native < static_cast<s32>(m_drawing_area.left))
  {
    s32 delta_native = static_cast<s32>(m_drawing_area.left) - x_native;
    x_native += delta_native;
    w_native -= delta_native;
  }

  if ((x_native + w_native) > (static_cast<s32>(m_drawing_area.right) + 1))
  {
    w_native = (static_cast<s32>(m_drawing_area.right + 1))  - x_native;
  }

  if (w_native <= 0)
    return;
#endif

#if USE_FLOAT_STEP
  i_group_float igf = {};

  igf.r = (float)igi.r / (1ll << (COORD_FBS + COORD_POST_PADDING));
  igf.g = (float)igi.g / (1ll << (COORD_FBS + COORD_POST_PADDING));
  igf.b = (float)igi.b / (1ll << (COORD_FBS + COORD_POST_PADDING));
  igf.u = (float)igi.u / (1ll << (COORD_FBS + COORD_POST_PADDING));
  igf.v = (float)igi.v / (1ll << (COORD_FBS + COORD_POST_PADDING));

  float postpad_scalar = 1ll << (COORD_FBS + COORD_POST_PADDING + (SCALE_ALL_VERTEX ? 0 : RESOLUTION_SHIFT));

  AddIDeltas_DX<shading_enable, texture_enable>(igf, idl, (float)x_ig_adjust / postpad_scalar);
  AddIDeltas_DY<shading_enable, texture_enable>(igf, idl, (float)y_up        / postpad_scalar);
#endif

#if USE_INT_STEP
  AddIDeltas_DX<shading_enable, texture_enable>(igi, idl, (float)x_ig_adjust / (SCALE_ALL_VERTEX ? 1 : RESOLUTION_SCALE));
  AddIDeltas_DY<shading_enable, texture_enable>(igi, idl, (float)y_up        / (SCALE_ALL_VERTEX ? 1 : RESOLUTION_SCALE));
#endif

  do
  {
    Assert(x_up <= static_cast<s32>(m_drawing_area.right+1) * RESOLUTION_SCALE);

#if USE_FLOAT_STEP
    auto r = Truncate8((int)floorf(igf.r));
    auto g = Truncate8((int)floorf(igf.g));
    auto b = Truncate8((int)floorf(igf.b));
    auto u = Truncate8((int)floorf(igf.u));
    auto v = Truncate8((int)floorf(igf.v));
#endif

#if USE_INT_STEP
    auto ri = Truncate8(igi.r >> (COORD_FBS + COORD_POST_PADDING)); // + RESOLUTION_SHIFT);
    auto gi = Truncate8(igi.g >> (COORD_FBS + COORD_POST_PADDING)); // + RESOLUTION_SHIFT);
    auto bi = Truncate8(igi.b >> (COORD_FBS + COORD_POST_PADDING)); // + RESOLUTION_SHIFT);
    auto ui = Truncate8(igi.u >> (COORD_FBS + COORD_POST_PADDING)); // + RESOLUTION_SHIFT);
    auto vi = Truncate8(igi.v >> (COORD_FBS + COORD_POST_PADDING)); // + RESOLUTION_SHIFT);
#endif

    //Assert(r == ri && u == ui);
    //Assert(g == gi && v == vi);
    //Assert(b == bi);

    // FIXME: also need to clip uprender right edge.
    if (x_up >= 0) {
      ShadePixel<texture_enable, raw_texture_enable, transparency_enable, dithering_enable>(
        cmd, x_up, y_up,
#if USE_INT_STEP
        ri, gi, bi, ui, vi
#else
        r, g, b, u, v
#endif
      );
    }
    x_up++;

#if USE_FLOAT_STEP
    AddIDeltas_DX<shading_enable, texture_enable>(igf, idl, 1.0f / postpad_scalar);
#endif

#if USE_INT_STEP
    AddIDeltas_DX<shading_enable, texture_enable>(igi, idl, 1.0f / (SCALE_ALL_VERTEX ? 1 : RESOLUTION_SCALE));
#endif

  } while (--w_up > 0);
}

template<bool shading_enable, bool texture_enable, bool raw_texture_enable, bool transparency_enable,
         bool dithering_enable>
void GPU_SW_Backend::DrawTriangle(const GPUBackendDrawPolygonCommand* cmd,
                                  const GPUBackendDrawPolygonCommand::Vertex* v0n,
                                  const GPUBackendDrawPolygonCommand::Vertex* v1n,
                                  const GPUBackendDrawPolygonCommand::Vertex* v2n)
{
  u32 core_vertex;
  {
    u32 cvtemp = 0;

    if (v1n->x <= v0n->x)
    {
      if (v2n->x <= v1n->x)
        cvtemp = (1 << 2);
      else
        cvtemp = (1 << 1);
    }
    else if (v2n->x < v0n->x)
      cvtemp = (1 << 2);
    else
      cvtemp = (1 << 0);

    if (v2n->y < v1n->y)
    {
      std::swap(v2n, v1n);
      cvtemp = ((cvtemp >> 1) & 0x2) | ((cvtemp << 1) & 0x4) | (cvtemp & 0x1);
    }

    if (v1n->y < v0n->y)
    {
      std::swap(v1n, v0n);
      cvtemp = ((cvtemp >> 1) & 0x1) | ((cvtemp << 1) & 0x2) | (cvtemp & 0x4);
    }

    if (v2n->y < v1n->y)
    {
      std::swap(v2n, v1n);
      cvtemp = ((cvtemp >> 1) & 0x2) | ((cvtemp << 1) & 0x4) | (cvtemp & 0x1);
    }

    core_vertex = cvtemp >> 1;
  }

  if (v0n->y == v2n->y)
    return;

  if (static_cast<u32>(std::abs(v2n->x - v0n->x)) >= MAX_PRIMITIVE_WIDTH ||
      static_cast<u32>(std::abs(v2n->x - v1n->x)) >= MAX_PRIMITIVE_WIDTH ||
      static_cast<u32>(std::abs(v1n->x - v0n->x)) >= MAX_PRIMITIVE_WIDTH ||
      static_cast<u32>(v2n->y - v0n->y) >= MAX_PRIMITIVE_HEIGHT)
  {
    return;
  }

  s64 bound_coord_us;
  s64 bound_coord_ls;
  bool right_facing;

  GPUBackendDrawPolygonCommand::Vertex up_v0 = *v0n;
  GPUBackendDrawPolygonCommand::Vertex up_v1 = *v1n;
  GPUBackendDrawPolygonCommand::Vertex up_v2 = *v2n;

  GPUBackendDrawPolygonCommand::Vertex* v0 = &up_v0;
  GPUBackendDrawPolygonCommand::Vertex* v1 = &up_v1;
  GPUBackendDrawPolygonCommand::Vertex* v2 = &up_v2;

#if SCALE_ALL_VERTEX
  v0->x *= RESOLUTION_SCALE;
  v0->y *= RESOLUTION_SCALE;
  v1->x *= RESOLUTION_SCALE;
  v1->y *= RESOLUTION_SCALE;
  v2->x *= RESOLUTION_SCALE;
  v2->y *= RESOLUTION_SCALE;
#endif

  s64 base_coord = MakePolyXFP(v0->x);
  s64 base_step = MakePolyXFPStep((v2->x - v0->x), (v2->y - v0->y));

  if (v1->y == v0->y)
  {
    bound_coord_us = 0;
    right_facing = (bool)(v1->x > v0->x);
  }
  else
  {
    bound_coord_us = MakePolyXFPStep((v1->x - v0->x), (v1->y - v0->y));
    right_facing = (bool)(bound_coord_us > base_step);
  }

  if (v2->y == v1->y)
    bound_coord_ls = 0;
  else
    bound_coord_ls = MakePolyXFPStep((v2->x - v1->x), (v2->y - v1->y));

  i_deltas idl;
  if (!CalcIDeltas<shading_enable, texture_enable>(idl, v0, v1, v2))
    return;

  const GPUBackendDrawPolygonCommand::Vertex* vertices[3] = {v0, v1, v2};
  int upshift = SCALE_ALL_VERTEX ? RESOLUTION_SHIFT : 0;
  int upmul = 1; //RESOLUTION_SCALE;

  i_group ig;
  if constexpr (texture_enable)
  {
    ig.u = (COORD_MF_INT(vertices[core_vertex]->u * upmul) + (1 << (COORD_FBS - 1 - upshift))) << COORD_POST_PADDING;
    ig.v = (COORD_MF_INT(vertices[core_vertex]->v * upmul) + (1 << (COORD_FBS - 1 - upshift))) << COORD_POST_PADDING;
  }

  ig.r = (COORD_MF_INT(vertices[core_vertex]->r * upmul) + (1 << (COORD_FBS - 1 - upshift))) << COORD_POST_PADDING;
  ig.g = (COORD_MF_INT(vertices[core_vertex]->g * upmul) + (1 << (COORD_FBS - 1 - upshift))) << COORD_POST_PADDING;
  ig.b = (COORD_MF_INT(vertices[core_vertex]->b * upmul) + (1 << (COORD_FBS - 1 - upshift))) << COORD_POST_PADDING;

  AddIDeltas_DX<shading_enable, texture_enable>(ig, idl, -vertices[core_vertex]->x);
  AddIDeltas_DY<shading_enable, texture_enable>(ig, idl, -vertices[core_vertex]->y);

  struct TriangleHalf
  {
    u64 x_coord[2];
    u64 x_step[2];

    s32 y_coord;
    s32 y_bound;

    bool dec_mode;
  } tripart[2];

  u32 vo = 0;
  u32 vp = 0;
  if (core_vertex != 0)
    vo = 1;
  if (core_vertex == 2)
    vp = 3;

  {
    TriangleHalf* tp = &tripart[vo];
    tp->y_coord = vertices[0 ^ vo]->y;
    tp->y_bound = vertices[1 ^ vo]->y;
    tp->x_coord[right_facing] = MakePolyXFP(vertices[0 ^ vo]->x);
    tp->x_step[right_facing] = bound_coord_us;
    tp->x_coord[!right_facing] = base_coord + ((vertices[vo]->y - vertices[0]->y) * base_step);
    tp->x_step[!right_facing] = base_step;
    tp->dec_mode = vo;
  }

  {
    TriangleHalf* tp = &tripart[vo ^ 1];
    tp->y_coord = vertices[1 ^ vp]->y;
    tp->y_bound = vertices[2 ^ vp]->y;
    tp->x_coord[right_facing] = MakePolyXFP(vertices[1 ^ vp]->x);
    tp->x_step[right_facing] = bound_coord_ls;
    tp->x_coord[!right_facing] =
      base_coord + ((vertices[1 ^ vp]->y - vertices[0]->y) *
                    base_step); // base_coord + ((vertices[1].y - vertices[0].y) * base_step);
    tp->x_step[!right_facing] = base_step;
    tp->dec_mode = vp;
  }

  for (u32 i = 0; i < 2; i++)
  {
    auto scalar = SCALE_ALL_VERTEX ? 1 : RESOLUTION_SCALE;

    s32 yi = tripart[i].y_coord * scalar;
    s32 yb = tripart[i].y_bound * scalar;

    u64 lc = tripart[i].x_coord[0] * scalar;
    u64 ls = tripart[i].x_step[0];

    u64 rc = tripart[i].x_coord[1] * scalar;
    u64 rs = tripart[i].x_step[1];

    if (tripart[i].dec_mode)
    {
      while (yi > yb)
      {
        yi--;
        lc -= ls;
        rc -= rs;

        s32 y = SignExtendN<11 + RESOLUTION_SHIFT, s32>(yi);

        if (y < static_cast<s32>(m_drawing_area.top) * RESOLUTION_SCALE)
          break;

        if (y > (static_cast<s32>(m_drawing_area.bottom) * RESOLUTION_SCALE) + 1)
          continue;

        DrawSpan<shading_enable, texture_enable, raw_texture_enable, transparency_enable, dithering_enable>(
          cmd, yi, GetPolyXFP_Int(lc), GetPolyXFP_Int(rc), ig, idl);
      }
    }
    else
    {
      while (yi < yb)
      {
        s32 y = SignExtendN<11 + RESOLUTION_SHIFT, s32>(yi);

        if (y > static_cast<s32>(m_drawing_area.bottom)* RESOLUTION_SCALE)
          break;

        if (y >= static_cast<s32>(m_drawing_area.top)* RESOLUTION_SCALE)
        {
          DrawSpan<shading_enable, texture_enable, raw_texture_enable, transparency_enable, dithering_enable>(
            cmd, yi, GetPolyXFP_Int(lc), GetPolyXFP_Int(rc), ig, idl);
        }

        yi++;
        lc += ls;
        rc += rs;
      }
    }
  }
}

GPU_SW_Backend::DrawTriangleFunction GPU_SW_Backend::GetDrawTriangleFunction(bool shading_enable, bool texture_enable,
                                                                             bool raw_texture_enable,
                                                                             bool transparency_enable,
                                                                             bool dithering_enable)
{
#define F(SHADING, TEXTURE, RAW_TEXTURE, TRANSPARENCY, DITHERING)                                                      \
  &GPU_SW_Backend::DrawTriangle<SHADING, TEXTURE, RAW_TEXTURE, TRANSPARENCY, DITHERING>

  static constexpr DrawTriangleFunction funcs[2][2][2][2][2] = {
    {{{{F(false, false, false, false, false), F(false, false, false, false, true)},
       {F(false, false, false, true, false), F(false, false, false, true, true)}},
      {{F(false, false, true, false, false), F(false, false, true, false, true)},
       {F(false, false, true, true, false), F(false, false, true, true, true)}}},
     {{{F(false, true, false, false, false), F(false, true, false, false, true)},
       {F(false, true, false, true, false), F(false, true, false, true, true)}},
      {{F(false, true, true, false, false), F(false, true, true, false, true)},
       {F(false, true, true, true, false), F(false, true, true, true, true)}}}},
    {{{{F(true, false, false, false, false), F(true, false, false, false, true)},
       {F(true, false, false, true, false), F(true, false, false, true, true)}},
      {{F(true, false, true, false, false), F(true, false, true, false, true)},
       {F(true, false, true, true, false), F(true, false, true, true, true)}}},
     {{{F(true, true, false, false, false), F(true, true, false, false, true)},
       {F(true, true, false, true, false), F(true, true, false, true, true)}},
      {{F(true, true, true, false, false), F(true, true, true, false, true)},
       {F(true, true, true, true, false), F(true, true, true, true, true)}}}}};

#undef F

  return funcs[u8(shading_enable)][u8(texture_enable)][u8(raw_texture_enable)][u8(transparency_enable)]
              [u8(dithering_enable)];
}

enum
{
  Line_XY_FractBits = 32
};
enum
{
  Line_RGB_FractBits = 12
};

struct line_fxp_coord
{
  u64 x, y;
  u32 r, g, b;
};

struct line_fxp_step
{
  s64 dx_dk, dy_dk;
  s32 dr_dk, dg_dk, db_dk;
};

static ALWAYS_INLINE_RELEASE s64 LineDivide(s64 delta, s32 dk)
{
  delta = (u64)delta << Line_XY_FractBits;

  if (delta < 0)
    delta -= dk - 1;
  if (delta > 0)
    delta += dk - 1;

  return (delta / dk);
}

template<bool shading_enable, bool transparency_enable, bool dithering_enable>
void GPU_SW_Backend::DrawLine(const GPUBackendDrawLineCommand* cmd, const GPUBackendDrawLineCommand::Vertex* p0,
                              const GPUBackendDrawLineCommand::Vertex* p1)
{
  const s32 i_dx = std::abs(p1->x - p0->x);
  const s32 i_dy = std::abs(p1->y - p0->y);
  const s32 k = (i_dx > i_dy) ? i_dx : i_dy;
  if (i_dx >= MAX_PRIMITIVE_WIDTH || i_dy >= MAX_PRIMITIVE_HEIGHT)
    return;

  if (p0->x >= p1->x && k > 0)
    std::swap(p0, p1);

  line_fxp_step step;
  if (k == 0)
  {
    step.dx_dk = 0;
    step.dy_dk = 0;

    if constexpr (shading_enable)
    {
      step.dr_dk = 0;
      step.dg_dk = 0;
      step.db_dk = 0;
    }
  }
  else
  {
    step.dx_dk = LineDivide(p1->x - p0->x, k);
    step.dy_dk = LineDivide(p1->y - p0->y, k);

    if constexpr (shading_enable)
    {
      step.dr_dk = (s32)((u32)(p1->r - p0->r) << Line_RGB_FractBits) / k;
      step.dg_dk = (s32)((u32)(p1->g - p0->g) << Line_RGB_FractBits) / k;
      step.db_dk = (s32)((u32)(p1->b - p0->b) << Line_RGB_FractBits) / k;
    }
  }

  line_fxp_coord cur_point;
  cur_point.x = ((u64)p0->x << Line_XY_FractBits) | (1ULL << (Line_XY_FractBits - 1));
  cur_point.y = ((u64)p0->y << Line_XY_FractBits) | (1ULL << (Line_XY_FractBits - 1));

  cur_point.x -= 1024;

  if (step.dy_dk < 0)
    cur_point.y -= 1024;

  if constexpr (shading_enable)
  {
    cur_point.r = (p0->r << Line_RGB_FractBits) | (1 << (Line_RGB_FractBits - 1));
    cur_point.g = (p0->g << Line_RGB_FractBits) | (1 << (Line_RGB_FractBits - 1));
    cur_point.b = (p0->b << Line_RGB_FractBits) | (1 << (Line_RGB_FractBits - 1));
  }

  for (s32 i = 0; i <= k; i++)
  {
    // Sign extension is not necessary here for x and y, due to the maximum values that ClipX1 and ClipY1 can contain.
    const s32 x = (cur_point.x >> Line_XY_FractBits) & 2047;
    const s32 y = (cur_point.y >> Line_XY_FractBits) & 2047;

    if ((!cmd->params.interlaced_rendering || cmd->params.active_line_lsb != (Truncate8(static_cast<u32>(y)) & 1u)) &&
        x >= static_cast<s32>(m_drawing_area.left) && x <= static_cast<s32>(m_drawing_area.right) &&
        y >= static_cast<s32>(m_drawing_area.top) && y <= static_cast<s32>(m_drawing_area.bottom))
    {
      const u8 r = shading_enable ? static_cast<u8>(cur_point.r >> Line_RGB_FractBits) : p0->r;
      const u8 g = shading_enable ? static_cast<u8>(cur_point.g >> Line_RGB_FractBits) : p0->g;
      const u8 b = shading_enable ? static_cast<u8>(cur_point.b >> Line_RGB_FractBits) : p0->b;

      // FIXME: this is sufficient for horizontal or vertical lines, but diaglonals will likely
      // need more advanced heuristics or anti-aliasing to avoid looking ugly and/or causing unsightly
      // coverage artifacts.

      for (int yu=0; yu<RESOLUTION_SCALE; ++yu)
      {
        for (int xu=0; xu<RESOLUTION_SCALE; ++xu)
        {
          ShadePixel<false, false, transparency_enable, dithering_enable>(cmd,
            static_cast<u32>((x * RESOLUTION_SCALE) + xu),
            static_cast<u32>((y * RESOLUTION_SCALE) + yu),
            r, g, b, 0, 0
          );
        }
      }
    }
    cur_point.x += step.dx_dk;
    cur_point.y += step.dy_dk;

    if constexpr (shading_enable)
    {
      cur_point.r += step.dr_dk;
      cur_point.g += step.dg_dk;
      cur_point.b += step.db_dk;
    }
  }
}

GPU_SW_Backend::DrawLineFunction GPU_SW_Backend::GetDrawLineFunction(bool shading_enable, bool transparency_enable,
                                                                     bool dithering_enable)
{
#define F(SHADING, TRANSPARENCY, DITHERING) &GPU_SW_Backend::DrawLine<SHADING, TRANSPARENCY, DITHERING>

  static constexpr DrawLineFunction funcs[2][2][2] = {
    {{F(false, false, false), F(false, false, true)}, {F(false, true, false), F(false, true, true)}},
    {{F(true, false, false), F(true, false, true)}, {F(true, true, false), F(true, true, true)}}};

#undef F

  return funcs[u8(shading_enable)][u8(transparency_enable)][u8(dithering_enable)];
}

GPU_SW_Backend::DrawRectangleFunction
GPU_SW_Backend::GetDrawRectangleFunction(bool texture_enable, bool raw_texture_enable, bool transparency_enable)
{
#define F(TEXTURE, RAW_TEXTURE, TRANSPARENCY) &GPU_SW_Backend::DrawRectangle<TEXTURE, RAW_TEXTURE, TRANSPARENCY>

  static constexpr DrawRectangleFunction funcs[2][2][2] = {
    {{F(false, false, false), F(false, false, true)}, {F(false, true, false), F(false, true, true)}},
    {{F(true, false, false), F(true, false, true)}, {F(true, true, false), F(true, true, true)}}};

#undef F

  return funcs[u8(texture_enable)][u8(raw_texture_enable)][u8(transparency_enable)];
}

void GPU_SW_Backend::FillVRAM(u32 x, u32 y, u32 width, u32 height, u32 color, GPUBackendCommandParameters params)
{
  const u16 color16 = VRAMRGBA8888ToRGBA5551(color);

  if constexpr (RESOLUTION_SCALE == 1)
  {
    if ((x + width) <= VRAM_WIDTH && !params.interlaced_rendering)
    {
      for (u32 yoffs = 0; yoffs < height; yoffs++)
      {
        const u32 row = (y + yoffs) % VRAM_HEIGHT;
        std::fill_n(&UPRAM_ACCESSOR[row * VRAM_WIDTH + x], width, color16);
      }
    }
    else if (params.interlaced_rendering)
    {
      // Hardware tests show that fills seem to break on the first two lines when the offset matches the displayed field.
      const u32 active_field = params.active_line_lsb;
      for (u32 yoffs = 0; yoffs < height; yoffs++)
      {
        const u32 row = (y + yoffs) % VRAM_HEIGHT;
        if ((row & u32(1)) == active_field)
          continue;
           
        u16* row_ptr = &UPRAM_ACCESSOR[row * VRAM_WIDTH];
        for (u32 xoffs = 0; xoffs < width; xoffs++)
        {
          const u32 col = (x + xoffs) % VRAM_WIDTH;
          row_ptr[col] = color16;
        }
      }
    }
    else
    {
      for (u32 yoffs = 0; yoffs < height; yoffs++)
      {
        const u32 row = (y + yoffs) % VRAM_HEIGHT;
        u16* row_ptr = &UPRAM_ACCESSOR[row * VRAM_WIDTH];
        for (u32 xoffs = 0; xoffs < width; xoffs++)
        {
          const u32 col = (x + xoffs) % VRAM_WIDTH;
          row_ptr[col] = color16;
        }
      }
    }
  }
  else
  {
    const u32 active_field = params.active_line_lsb;
    for (u32 yoffs = 0; yoffs < height; yoffs++)
    {
      for(u32 xoffs = 0; xoffs < width; xoffs++)
      {
        const u32 row = (y + yoffs) % VRAM_HEIGHT;
        if (params.interlaced_rendering && (row & u32(1)) == active_field)
          continue;

        SetPixel(x+xoffs, y+yoffs, color16);
      }
    }
  }
}


void GPU_SW_Backend::UpdateVRAM(u32 x, u32 y, u32 width, u32 height, const void* data,
                                GPUBackendCommandParameters params)
{
  // Fast path when the copy is not oversized.
  if ((x + width) <= VRAM_WIDTH && (y + height) <= VRAM_HEIGHT && !params.IsMaskingEnabled())
  {
    const u16* src_ptr = static_cast<const u16*>(data);
    if constexpr (RESOLUTION_SCALE == 1)
    {
      u16* dst_ptr = &UPRAM_ACCESSOR[y * VRAM_WIDTH + x];
      for (u32 yoffs = 0; yoffs < height; yoffs++)
      {
        std::copy_n(src_ptr, width, dst_ptr);
        src_ptr += width;
        dst_ptr += VRAM_WIDTH;
      }
    }
    else
    {
      for (u32 yoffs = 0; yoffs < height; yoffs++)
      {
        for(u32 xoffs = 0; xoffs < width; xoffs++, src_ptr++)
        {
          SetPixel(x+xoffs, y+yoffs, src_ptr[0]);
        }
      }
    }
  }
  else
  {
    // Slow path when we need to handle wrap-around.
    const u16* src_ptr = static_cast<const u16*>(data);
    const u16 mask_and = params.GetMaskAND();
    const u16 mask_or = params.GetMaskOR();

    for (u32 row = 0; row < height;)
    {
      u16* dst_row_ptr = &UPRAM_ACCESSOR[((y + row++) % VRAM_HEIGHT) * VRAM_WIDTH];
      for (u32 col = 0; col < width;)
      {
        // TODO: Handle unaligned reads...
        u16* pixel_ptr = &dst_row_ptr[(x + col++) % VRAM_WIDTH];
        if (((*pixel_ptr) & mask_and) == 0)
          *pixel_ptr = *(src_ptr++) | mask_or;
      }
    }
  }
}

void GPU_SW_Backend::ReadVRAM(u32 x, u32 y, u32 width, u32 height)
{
  // copy from m_upram_ptr to m_vram_ptr using simple sparse read logic.

  auto* shadow_ptr = GetVRAMshadowPtr();

  for (u32 yoffs = 0; yoffs < height; yoffs++)
  {
    const u32 row = (y + yoffs) % VRAM_HEIGHT;
    const u16* src = UPRAM_ACCESSOR + (row * VRAM_UPRENDER_SIZE_X);
          u16* dst = shadow_ptr     + (row);
    for (u32 xoffs = 0; xoffs < width; xoffs++)
    {
      const u32 col = (x + xoffs) % VRAM_WIDTH;
      dst[col] = src[col * RESOLUTION_SCALE];
    }
  }

}

void GPU_SW_Backend::Sync(bool allow_sleep) 
{
  GPUBackend::Sync(allow_sleep);
  ReadVRAM(0, 0, VRAM_WIDTH, VRAM_HEIGHT);
}


void GPU_SW_Backend::CopyVRAM(u32 src_x, u32 src_y, u32 dst_x, u32 dst_y, u32 width, u32 height,
                              GPUBackendCommandParameters params)
{
  // Break up oversized copies. This behavior has not been verified on console.
  if ((src_x + width) > VRAM_WIDTH || (dst_x + width) > VRAM_WIDTH)
  {
    u32 remaining_rows = height;
    u32 current_src_y = src_y;
    u32 current_dst_y = dst_y;
    while (remaining_rows > 0)
    {
      const u32 rows_to_copy =
        std::min<u32>(remaining_rows, std::min<u32>(VRAM_HEIGHT - current_src_y, VRAM_HEIGHT - current_dst_y));

      u32 remaining_columns = width;
      u32 current_src_x = src_x;
      u32 current_dst_x = dst_x;
      while (remaining_columns > 0)
      {
        const u32 columns_to_copy =
          std::min<u32>(remaining_columns, std::min<u32>(VRAM_WIDTH - current_src_x, VRAM_WIDTH - current_dst_x));
        CopyVRAM(current_src_x, current_src_y, current_dst_x, current_dst_y, columns_to_copy, rows_to_copy, params);
        current_src_x = (current_src_x + columns_to_copy) % VRAM_WIDTH;
        current_dst_x = (current_dst_x + columns_to_copy) % VRAM_WIDTH;
        remaining_columns -= columns_to_copy;
      }

      current_src_y = (current_src_y + rows_to_copy) % VRAM_HEIGHT;
      current_dst_y = (current_dst_y + rows_to_copy) % VRAM_HEIGHT;
      remaining_rows -= rows_to_copy;
    }

    return;
  }

  // This doesn't have a fast path, but do we really need one? It's not common.
  const u16 mask_and = params.GetMaskAND();
  const u16 mask_or = params.GetMaskOR();

  // Copy in reverse when src_x < dst_x, this is verified on console.
  if (src_x < dst_x || ((src_x + width - 1) % VRAM_WIDTH) < ((dst_x + width - 1) % VRAM_WIDTH))
  {
    for (u32 row = 0; row < height; row++)
    {
      const u16* src_row_ptr = &UPRAM_ACCESSOR[((src_y + row) % VRAM_HEIGHT) * VRAM_WIDTH];
      u16* dst_row_ptr = &UPRAM_ACCESSOR[((dst_y + row) % VRAM_HEIGHT) * VRAM_WIDTH];

      for (s32 col = static_cast<s32>(width - 1); col >= 0; col--)
      {
        const u16 src_pixel = src_row_ptr[(src_x + static_cast<u32>(col)) % VRAM_WIDTH];
        u16* dst_pixel_ptr = &dst_row_ptr[(dst_x + static_cast<u32>(col)) % VRAM_WIDTH];
        if ((*dst_pixel_ptr & mask_and) == 0)
          *dst_pixel_ptr = src_pixel | mask_or;
      }
    }
  }
  else
  {
    for (u32 row = 0; row < height; row++)
    {
      const u16* src_row_ptr = &UPRAM_ACCESSOR[((src_y + row) % VRAM_HEIGHT) * VRAM_WIDTH];
      u16* dst_row_ptr = &UPRAM_ACCESSOR[((dst_y + row) % VRAM_HEIGHT) * VRAM_WIDTH];

      for (u32 col = 0; col < width; col++)
      {
        const u16 src_pixel = src_row_ptr[(src_x + col) % VRAM_WIDTH];
        u16* dst_pixel_ptr = &dst_row_ptr[(dst_x + col) % VRAM_WIDTH];
        if ((*dst_pixel_ptr & mask_and) == 0)
          *dst_pixel_ptr = src_pixel | mask_or;
      }
    }
  }
}

void GPU_SW_Backend::FlushRender() {}

void GPU_SW_Backend::DrawingAreaChanged() {}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
