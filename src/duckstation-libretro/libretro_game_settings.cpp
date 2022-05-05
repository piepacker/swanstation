#include <unordered_set>
#include "libretro_game_settings.h"

std::unique_ptr<GameSettings::Entry> GetSettingsForGame(const std::string& game_code)
{
    std::unique_ptr<GameSettings::Entry> gs = std::make_unique<GameSettings::Entry>();
    // Note: if performance of string cmp is too horrible, we can precompute hash to speed up
    // process
    if (game_code == "HPS-105") { // Wai Wai Trump Taisen [Controller Set]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "HPS-91") { // Wai Wai 3-nin Uchi Mahjong [Controller Set]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "PAPX-90097") { // PAPX-90097 (Alundra 2 - Mashinka no Nazo (Japan) (Demo))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCED-01979") { // SCED-01979 (Formula One '99 (Europe) (En,Fr,De,It) (Beta))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-00002") { // SCES-00002 (Battle Arena Toshinden (Europe))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCES-00067") { // Total NBA '96 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-00263") { // Namco Tennis Smash Court (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-00269") { // Galaxian^3 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-00392") { // NHL Face Off '97 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-00408") { // Rally Cross (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-00623") { // Total NBA '97 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-00842") { // SCES-00842 (Armored Core (Europe) (En,Fr,De,Es,It))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SCES-00867") { // SCES-00867 (Final Fantasy VII (Europe) (Disc 1))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-00868") { // SCES-00868 (Final Fantasy VII (Italy) (Disc 1))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-00869") { // SCES-00869 (Final Fantasy VII (Germany) (Disc 1))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-00900") { // SCES-00900 (Final Fantasy VII (Spain) (Disc 1))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-00983") { // Everybody's Golf (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01022") { // NHL FaceOff 98 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01043") { // Cardinal Syn (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01077") { // Cardinal Syn (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01078") { // Bomberman World (Europe, Australia) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01079") { // Total NBA 98 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01205") { // Cardinal Syn (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01206") { // Cardinal Syn (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01224") { // SCES-01224 (Blasto (Europe) (En,Fr,De,Es,It))
        gs->display_line_start_offset = 1;
        return gs;
    }
    if (game_code == "SCES-01312") { // Devil Dice (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SCES-01438") { // SCES-01438 (Spyro the Dragon (Europe) (En,Fr,De,Es,It))
        gs->AddTrait(GameSettings::Trait::DisablePGXPCulling);
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCES-01443") { // Blood Lines (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01630") { // Running Wild (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01700") { // This Is Football (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01701") { // Monde des Bleus, Le - Le Jeu Officiel de l'Equipe de France (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01702") { // Fussball Live (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01703") { // This Is Football (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01704") { // Esto Es Futbol (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01736") { // NHL FaceOff 99 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01752") { // SCES-01752 (Legend of Legaia (Europe))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCES-01763") { // Speed Freaks (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01833") { // Anna Kournikova's Smash Court Tennis (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01882") { // This Is Football (Europe) (Fr,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01923") { // Team Buddies (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-01944") { // SCES-01944 (Legend of Legaia (France))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCES-01945") { // SCES-01945 (Legend of Legaia (Germany))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCES-01946") { // SCES-01946 (Legend of Legaia (Italy))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCES-01947") { // SCES-01947 (Legend of Legaia (Spain))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCES-01979") { // SCES-01979 (Formula One 99 (Europe) (En,Fr,De,It))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-02060") { // Destruction Derby Raw (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-02104") { // SCES-02104 (Spyro 2 - Gateway to Glimmer (Europe) (En,Fr,De,Es,It))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCES-02105") { // CTR - Crash Team Racing (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-02146") { // Everybody's Golf 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-02222") { // SCES-02222 (Formula One 99 (Europe) (En,Es,Fi))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-02269") { // This Is Soccer (Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-02451") { // NHL FaceOff 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-02777") { // SCES-02777 (Formula One 2000 (Europe) (En,Fi))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-02778") { // SCES-02778 (Formula One 2000 (Europe) (Fr,De))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-02779") { // SCES-02779 (Formula One 2000 (Europe) (Es,It))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-02834") { // Crash Bash (Europe) (En,Fr,De,Es,It)
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-02835") { // SCES-02835 (Spyro - Year of the Dragon (Europe) (En,Fr,De,Es,It))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCES-02986") { // Team Buddies (Europe) (En,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03000") { // SCES-03000 (Disney's Aladdin in Nasira's Revenge (Europe))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCES-03070") { // This Is Football 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03071") { // This Is Soccer 2 (Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03072") { // This Is Football 2 (Netherlands)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03073") { // Monde des Bleus 2, Le (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03074") { // Fussball Live 2 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03075") { // This Is Football 2 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03076") { // Esto Es Futbol 2 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03085") { // Ms. Pac-Man Maze Madness (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03086") { // Ms Pac-Man - Maze Madness
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03087") { // Ms Pac-Man - Maze Madness
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03236") { // This Is Football 2 (Belgium)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03404") { // SCES-03404 (Formula One 2001 (Europe) (En,Fi))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-03423") { // SCES-03423 (Formula One 2001 (Europe) (Fr,De))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-03424") { // SCES-03424 (Formula One 2001 (Europe) (Es,It))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-03524") { // SCES-03524 (Formula One 2001 (Russia))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-03705") { // Disney's Party Time with Winnie the Pooh (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03706") { // Disney's Winnie L'Ourson - C' Est La Recre! (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03745") { // Disney's Party mit Winnie Puuh (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03746") { // Disney's Spelen met Winnie de Poeh en zijn Vriendjes! (Netherlands)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03747") { // Disneys Plys' Spil-og-Leg-Sted (Denmark)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03748") { // Disney Ven a la Fiesta! con Winnie the Pooh (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03749") { // Disney Pooh e Tigro! E Qui la Festa (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-03886") { // SCES-03886 (Formula One Arcade (Europe) (En,Fr,De,Es,It))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCES-03922") { // Klonoa Beach Volleyball (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCES-10867") { // SCES-10867 (Final Fantasy VII (Europe) (Disc 2))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-10868") { // SCES-10868 (Final Fantasy VII (Italy) (Disc 2))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-10869") { // SCES-10869 (Final Fantasy VII (Germany) (Disc 2))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-10900") { // SCES-10900 (Final Fantasy VII (Spain) (Disc 2))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-20867") { // SCES-20867 (Final Fantasy VII (Europe) (Disc 3))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-20868") { // SCES-20868 (Final Fantasy VII (Italy) (Disc 3))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-20869") { // SCES-20869 (Final Fantasy VII (Germany) (Disc 3))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCES-20900") { // SCES-20900 (Final Fantasy VII (Spain) (Disc 3))
        gs->display_active_start_offset = -44;
        return gs;
    }
    if (game_code == "SCPS-10042" || game_code == "SCPS-91126") { // Minna no Golf (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-10051" || game_code == "SCPS-91166" || game_code == "SCPS-91303") { // XI [sai] (Japan) (En,Ja)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-10059") { // SCPS-10059 (Legaia Densetsu (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCPS-10085") { // SCPS-10085 (Spyro the Dragon (Japan))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCPS-10093") { // Minna no Golf 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-10101") { // SCPS-10101 (Formula One 99 (Japan))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SCPS-10115") { // SCPS-10115 (Alundra 2 - Mashinka no Nazo (Japan))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCPS-10118" || game_code == "SCPS-91328") { // Crash Bandicoot Racing (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-10126") { // SCPS-10126 (Addie no Okurimono - To Moze from Addie (Japan))
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        return gs;
    }
    if (game_code == "SCPS-10135") { // Magical Dice Kids (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-10140" || game_code == "SCPS-91319") { // Crash Bandicoot Carnival (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45034" || game_code == "SLPS-00785") { // SD Gundam - GCentury (Japan, Asia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45120") { // SCPS-45120 (Lagnacure (Japan, Asia))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SCPS-45168") { // Bomberman World
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45197") { // International Track & Field
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45268") { // XI [Sai]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45294") { // SCPS-45294 (International Superstar Soccer Pro '98 (Asia))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCPS-45404") { // SCPS-45404 (Racing Lagoon (Japan, Asia))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCPS-45421") { // Minna no Golf 2
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45470") { // Crash Bandicoot Racing
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45507" || game_code == "SCPS-45508" || game_code == "SCPS-45509") { // Tales of Eternia
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45511") { // Crash Bandicoot Carnival
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-45516") { // Klonoa Beach Volleball
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-91197") { // Minna no Golf 2 (Japan) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCPS-91230") { // Crash Bandicoot Racing [Playstation the Best for Family]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94003") { // SCUS-94003 (Battle Arena Toshinden (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCUS-94156") { // Cardinal Syn (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94171") { // NBA ShootOut 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94172") { // NCAA GameBreaker 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94173") { // NFL GameDay 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94174") { // NHL FaceOff 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94182") { // SCUS-94182 (Armored Core (USA))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SCUS-94188") { // Hot Shots Golf (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94200") { // SCUS-94200 (Battle Arena Toshinden (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCUS-94228") { // SCUS-94228 (Spyro the Dragon (USA))
        gs->AddTrait(GameSettings::Trait::DisablePGXPCulling);
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCUS-94234" || game_code == "SCUS-94274") { // NFL GameDay 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94235") { // NHL FaceOff 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94243") { // SCUS-94243 (Einhaender (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SCUS-94246") { // NCAA GameBreaker 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94249") { // Twisted Metal III (USA)
        gs->multitap_mode = MultitapMode::Port2Only;
        return gs;
    }
    if (game_code == "SCUS-94254") { // SCUS-94254 (Legend of Legaia (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCUS-94264" || game_code == "SCUS-94361") { // NCAA Final Four 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94272") { // Running Wild (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94290") { // SCUS-94290 (Spyro the Dragon (USA) (Demo 1))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCUS-94308") { // Rally Cross (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94420") { // NFL Xtreme 2 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94425") { // SCUS-94425 (Spyro 2 - Ripto's Rage! (USA))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCUS-94426") { // CTR - Crash Team Racing (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94457") { // SCUS-94457 (Grandia (USA) (Disc 1))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCUS-94465") { // SCUS-94465 (Grandia (USA) (Disc 2))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCUS-94467") { // SCUS-94467 (Spyro - Year of the Dragon (USA))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCUS-94476") { // Hot Shots Golf 2 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94500") { // NBA Shoot Out (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94502") { // Adidas Power Soccer (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94509") { // NCAA Football GameBreaker (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94510") { // NFL GameDay 97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94550") { // NHL Face Off '97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94551") { // Professional Underground League of Pain (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94552") { // NBA Shoot Out '97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94556") { // NFL GameDay 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94557") { // NCAA GameBreaker 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94558") { // NHL FaceOff 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94560") { // Twisted Metal 4 (USA)
        gs->multitap_mode = MultitapMode::Port2Only;
        return gs;
    }
    if (game_code == "SCUS-94561") { // NBA ShootOut 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94562") { // NCAA Final Four 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94563") { // Speed Punks (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94569") { // SCUS-94569 (Disney's Aladdin in Nasira's Revenge (USA))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SCUS-94570") { // Crash Bash (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94573") { // NCAA GameBreaker 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94575") { // NFL GameDay 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94577") { // NHL FaceOff 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCUS-94578") { // SCUS-94578 (NHL FaceOff 2001 (USA) (Demo))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SCUS-94579") { // NCAA Final Four 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94581") { // NBA ShootOut 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94639") { // NFL GameDay 2002 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94641") { // NBA ShootOut 2002 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94665") { // NFL GameDay 2003 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94673") { // NBA ShootOut 2003 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94690") { // NFL GameDay 2004 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94691") { // NBA ShootOut 2004 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SCUS-94695") { // NFL GameDay 2005 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SIPS-60008") { // Total NBA '96 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SIPS-60015") { // Total NBA '97 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SIPS-60018") { // NHL PowerRink '97 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SIPS-60022") { // Rally Cross (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLED-00038") { // SLED-00038 (Croc - Legend of the Gobbos (Europe) (Demo))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLED-00491") { // SLED-00491 (Formula One (Europe) (En,Fr,De,Es,It) (Demo))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SLED-00570") { // SLED-00570 (Pandemonium! (Europe) (Demo))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLED-01027") { // Duke Nukem (France) (Demo) (SLED-01027)
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLED-01310") { // SLED-01310 (Adidas Power Soccer 98 (France) (Demo))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLED-01311") { // SLED-01311 (Adidas Power Soccer 98 (Germany) (Demo))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLED-01401") { // SLED-01401 (International Superstar Soccer Pro '98 (Europe) (En,Fr,De,Es,It) (Demo))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLED-01513") { // SLED-01513 (International Superstar Soccer Pro '98 (France) (Demo))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLED-02119") { // SLED-02119 (Croc 2 (Europe) (Demo))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLED-02439") { // Compilation 03 (Australia) (SLED-02439)
        gs->AddTrait(GameSettings::Trait::DisablePGXPCulling);
        return gs;
    }
    if (game_code == "SLED-02879") { // SLED-02879 (Tony Hawk's Pro Skater 2 (Australia) (Demo))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLED-03048") { // SLED-03048 (Tony Hawk's Pro Skater 2 (Europe) (Demo))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-00015") { // Actua Golf (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00016") { // Micro Machines V3 (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00021") { // Actua Soccer 2 (Europe) (En,Fr)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00023") { // Striker 96 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00044") { // Actua Golf 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00068") { // NBA Jam - Tournament Edition (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00076") { // Ninja - Shadow of Darkness (Europe) (Beta)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00080") { // Supersonic Racers (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00081") { // SLES-00081 (Defcon 5 (Europe))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLES-00095") { // 4-4-2 Soccer (Europe) (En,Fr,De,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00096") { // Davis Cup Complete Tennis (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00110") { // Olympic Games (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00113") { // Olympic Soccer (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00116") { // FIFA Soccer 96 (Europe) (En,Fr,De,Es,It,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00132") { // SLES-00132 (Doom (Europe))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLES-00146") { // SLES-00146 (Defcon 5 (Italy))
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLES-00147") { // SLES-00147 (Defcon 5 (Spain))
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLES-00148") { // SLES-00148 (Defcon 5 (Germany))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLES-00149") { // SLES-00149 (Defcon 5 (France))
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLES-00171") { // NBA in the Zone (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00188") { // Actua Ice Hockey (Europe) (En,Fr,De,Sv,Fi)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00189") { // Adidas Power Soccer (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00201") { // Pitball (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00212") { // Syndicate Wars (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00213") { // Syndicate Wars (Europe) (En,Fr,Es,It,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00217") { // Sampras Extreme Tennis (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00225") { // NBA Live 96 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00256") { // Trash It (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00258") { // Break Point (Europe) (En,Fr)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00259") { // Pro Pinball - The Web (Europe) (SLES-00259)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        return gs;
    }
    if (game_code == "SLES-00265") { // Actua Tennis (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00270") { // Adidas Power Soccer International '97 (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00284") { // Space Jam (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00286") { // WWF In Your House (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00296") { // Street Racer (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00309") { // Hyper Tennis - Final Match (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00310") { // Motor Mash (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00313") { // NHL Powerplay (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00333") { // International Track & Field (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00377") { // Jonah Lomu Rugby (Europe) (En,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00418") { // NHL Powerplay 98 (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00436") { // Madden NFL 97 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00449") { // NFL Quarterback Club 97 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00472") { // Riot (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00476") { // Blast Chamber (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00483") { // SLES-00483 (Worms Pinball (Europe) (En,Fr,De,Es,It))
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLES-00487") { // Final Doom (Europe) (SLES-00487)
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLES-00492") { // NHL 97 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00504") { // FIFA 97 (Europe) (En,Fr,De,Es,It,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00505") { // FIFA 97 (France) (En,Fr,De,Es,It,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00506") { // FIFA 97 (Germany) (En,Fr,De,Es,It,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00511") { // International Superstar Soccer Deluxe (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00512") { // NHL 98 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00517") { // NBA Live 97 (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00526") { // SLES-00526 (Pandemonium! (Europe))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLES-00529") { // NBA Jam Extreme (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-00533") { // NHL 97 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00534") { // Ten Pin Alley (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00548") { // Fantastic Four (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00560") { // NBA in the Zone 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00584") { // SLES-00584 (Star Wars - Rebel Assault II - The Hidden Empire (Germany) (Disc 1))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLES-00593") { // SLES-00593 (Croc - Legend of the Gobbos (Europe))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-00606") { // Pro Pinball - Timeshock! (Europe) (SLES-00606)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        return gs;
    }
    if (game_code == "SLES-00611") { // Jonah Lomu Rugby (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00624") { // NHL Breakaway 98 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00626") { // World League Basketball (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00643") { // SLES-00643 (Star Wars - Rebel Assault II - The Hidden Empire (Italy) (Disc 1))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLES-00644") { // SLES-00644 (Star Wars - Rebel Assault II - The Hidden Empire (Spain) (Disc 1))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLES-00654") { // SLES-00654 (Star Wars - Rebel Assault II - The Hidden Empire (Europe) (Disc 1))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLES-00656") { // SLES-00656 (Star Wars - Rebel Assault II - The Hidden Empire (France) (Disc 1))
        gs->gpu_max_run_ahead = 1;
        gs->dma_max_slice_ticks = 200;
        return gs;
    }
    if (game_code == "SLES-00691") { // Soccer '97 (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00703") { // Duke Nukem (Europe) (SLES-00703)
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLES-00704") { // Frogger (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00707") { // Risk (Europe) (En,Fr,De,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00712") { // Arcade's Greatest Hits - The Atari Collection 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00715") { // Super Football Champ (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00717") { // World League Soccer '98 (Europe) (En,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00747") { // All Star Soccer (Europe) (En,Fr,De,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00753") { // Circuit Breakers (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00759") { // Brian Lara Cricket (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00761") { // Viva Football (Europe) (En,Fr,De,Es,It,Pt)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00785") { // Poy Poy (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00804") { // WWF War Zone (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00845") { // Blaze & Blade - Eternal Quest (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00857") { // Adidas Power Soccer 2 (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00865") { // Overboard! (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00882") { // NBA Pro 98 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00904") { // Madden NFL 98 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00906") { // NBA Live 98 (Europe) (En,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00907") { // NHL 98 (Europe) (En,Sv,Fi)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00910") { // SLES-00910 (Road Rash 3D (Europe))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLES-00914") { // FIFA - Road to World Cup 98 (Europe) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00915") { // FIFA - En Route pour la Coupe du Monde 98 (France) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00916") { // FIFA - Die WM-Qualifikation 98 (Germany) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00917") { // FIFA - Road to World Cup 98 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00918") { // FIFA - Rumbo al Mundial 98 (Spain) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00935") { // Tennis Arena (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00945") { // Monopoly (Europe) (En,Fr,De,Es,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00951") { // NBA Live 98 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00952") { // NBA Live 98 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-00987") { // Duke Nukem (France) (SLES-00987)
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLES-00999") { // Nagano Winter Olympics '98 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01003") { // NBA Fastbreak '98 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01028") { // Actua Soccer 2 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01029") { // Actua Soccer 2 (Germany) (En,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01039") { // Kick Off World
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01041") { // Hogs of War (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01042") { // Actua Golf 3 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01061") { // Kick Off World (Europe, Australia) (En,Fr)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01062") { // Kick Off World (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01103") { // Rat Attack (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01157") { // SLES-01157 (Road Rash 3D (France))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLES-01158") { // SLES-01158 (Road Rash 3D (Germany))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLES-01160") { // Wayne Gretzky's 3D Hockey '98 (Europe) (En,Fr,De,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01166") { // World League Soccer '98 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01167") { // World League Soccer '98 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01175") { // Super Match Soccer (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01203") { // Puma Street Soccer (Europe) (En,Fr,De,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01210") { // Actua Soccer 3 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01211") { // Pro Pinball - Big Race USA (Europe) (SLES-01211)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        return gs;
    }
    if (game_code == "SLES-01218") { // SLES-01218 (International Superstar Soccer Pro '98 (Europe) (En,Fr,De,Es))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-01226") { // Actua Ice Hockey 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01239") { // Adidas Power Soccer 98 (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLES-01241") { // Gekido - Urban Fighters (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01264") { // SLES-01264 (International Superstar Soccer Pro '98 (Italy))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-01265") { // World Cup 98 (Europe) (En,Fr,De,Es,Nl,Sv,Da)
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01266") { // Coupe du Monde 98 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01267") { // Frankreich 98 - Die Fussball-WM (Germany) (En,Fr,De,Es,Nl,Sv,Da)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01268") { // World Cup 98 - Coppa del Mondo (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01269") { // Copa del Mundo - Francia '98 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01273") { // Legend of Foresia - La Contree Interdite (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01274") { // Blaze & Blade - Eternal Quest (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01286") { // S.C.A.R.S. (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port2Only;
        return gs;
    }
    if (game_code == "SLES-01327") { // Kick Off World (Europe) (Es,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01328") { // Kick Off World (Greece)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01341") { // Absolute Football (France) (En,Fr,De,Es,It,Pt)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01376") { // Brunswick Circuit Pro Bowling (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01396") { // Actua Tennis (Europe) (Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01427") { // Madden NFL 99 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01433") { // All Star Tennis '99 (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01436") { // Rival Schools - United by Fate (Europe) (Disc 1) (Evolution Disc)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01445") { // NHL 99 (Europe) (En,Fr,Sv,Fi)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01446") { // NBA Live 99 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01454") { // NBA Live 99 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01455") { // NBA Live 99 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01456") { // NBA Live 99 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01457") { // NBA Live 99 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01458") { // NHL 99 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01514") { // SLES-01514 (Silent Hill (Europe))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-01534") { // Quake II (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01536") { // Poy Poy 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01537") { // Pool Shark (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01559") { // Pro 18 - World Tour Golf (Europe) (En,Fr,De,Es,It,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01576") { // Shane Warne Cricket (Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01584") { // FIFA 99 (Europe) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01585") { // FIFA 99 (France) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01586") { // FIFA 99 (Germany) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01587") { // FIFA 99 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01588") { // FIFA 99 (Spain) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01594") { // Michael Owen's World League Soccer '99 (Europe) (En,Fr,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01622") { // UEFA Champions League - Season 1998-99 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01644") { // Actua Soccer 3 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01645") { // Actua Soccer 3 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01646") { // Actua Soccer 3 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01647") { // Actua Pool (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01658") { // Shaolin (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01674") { // Tiger Woods 99 PGA Tour Golf (Europe) (En,Fr,De,Es,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01733") { // UEFA Striker (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01744") { // UEFA Champions League - Saison 1998-99 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01745") { // UEFA Champions League - Saison 1998-99 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01746") { // UEFA Champions League - Stagione 1998-99 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01747") { // UEFA Champions League - Temporada 1998-99 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01875") { // AFL 99 (Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01893") { // Bomberman (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01907") { // V-Rally - Championship Edition 2 (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01921") { // Micro Maniacs (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01970") { // NBA Pro 99 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01972") { // South Park - Chef's Luv Shack (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01980") { // WWF Attitude (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-01987") { // SLES-01987 (Next Tetris, The (Europe) (En,Fr,De,Es,It,Nl))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-02020") { // Pong (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02021") { // Rampage 2 - Universal Tour (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02061") { // PGA European Tour Golf (Europe) (En,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02088") { // SLES-02088 (Croc 2 (Europe) (En,Fr,De,Es,It,Nl,Sv))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-02095") { // ISS Pro Evolution (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02142") { // F.A. Premier League Stars, The (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02143") { // Bundesliga Stars 2000 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02170") { // Wu-Tang - Taste the Pain (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02171") { // Wu-Tang - Shaolin Style (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02172") { // Wu-Tang - Shaolin Style (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02173") { // Wu-Tang - Taste the Pain (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02192") { // Madden NFL 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02193") { // WCW Mayhem (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02194") { // Sled Storm (Europe) (En,Fr,De,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02224") { // Music 2000 (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02225") { // NHL 2000 (Europe) (En,Sv,Fi)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02226") { // NHL 2000 (Europe) (Fr,Cs)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02227") { // NHL 2000 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02255") { // WWF Attitude (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02272") { // Yeh Yeh Tennis (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02292") { // Premier Manager 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02293") { // Canal+ Premier Manager (Europe) (Fr,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02298") { // NHL Championship 2000 (Europe) (En,Fr,De,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02299") { // NBA Basketball 2000 (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02315") { // FIFA 2000 (Europe) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02316") { // FIFA 2000 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02317") { // FIFA 2000 (Germany) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02318") { // FIFA 2000 (Spain) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02319") { // FIFA 2000 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02320") { // FIFA 2000 (Greece)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02321") { // FIFA 2000 (Israel)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02335") { // NFL Blitz 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02336") { // NBA Showtime - NBA on NBC (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02339") { // Arcade Party Pak (Europe, Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02358") { // NBA Live 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02359") { // NBA Live 2000 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02360") { // NBA Live 2000 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02361") { // NBA Live 2000 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02362") { // NBA Live 2000 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02370") { // CyberTiger (Europe) (En,Fr,De,Es,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02371") { // CyberTiger (Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02396") { // PGA European Tour Golf (Europe) (Fr,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02397") { // SLES-02397 (Grandia (Europe) (Disc 1))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-02398") { // SLES-02398 (Grandia (France) (Disc 1))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-02399") { // SLES-02399 (Grandia (Germany) (Disc 1))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-02424") { // ISS Pro Evolution (Europe) (Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02448") { // International Track & Field 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02466") { // Pro Pinball - Fantastic Journey (Europe) (SLES-02466)
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLES-02476") { // Caesars Palace 2000 - Millennium Gold Edition (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02499") { // Midnight in Vegas (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02513") { // NBA in the Zone 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02514") { // NHL Blades of Steel 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02535") { // ECW Hardcore Revolution (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02536") { // ECW Hardcore Revolution (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02537") { // Bishi Bashi Special (Europe)
        gs->multitap_mode = MultitapMode::Port2Only;
        return gs;
    }
    if (game_code == "SLES-02550") { // International Superstar Soccer (Europe) (En,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02551") { // Tiger Woods PGA Tour 2000 (Europe) (En,Fr,De,Es,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02552") { // Road Rash - Jailbreak (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02563") { // Anstoss - Premier Manager (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02572") { // TOCA World Touring Cars (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02573") { // TOCA World Touring Cars (Europe) (Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02577") { // UEFA Champions League - Season 1999-2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02578") { // UEFA Champions League - Season 1999-2000 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02579") { // UEFA Champions League - Season 1999-2000 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02580") { // UEFA Champions League - Season 1999-2000 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02581") { // UEFA Champions League - Season 1999-2000 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02595") { // Tiger Woods USA Tour 2000 (Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02600") { // SLES-02600 (Alundra 2 - A New Legend Begins (Europe))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-02601") { // SLES-02601 (Alundra 2 - Une Legende Est Nee (France))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-02602") { // SLES-02602 (Alundra 2 - Der Beginn einer neuen Legende (Germany))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-02605") { // SLES-02605 (Colin McRae Rally 2.0 (Europe) (En,Fr,De,Es,It))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-02618") { // Brunswick Circuit Pro Bowling 2 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02619") { // WWF SmackDown! (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02689") { // Need for Speed - Porsche 2000 (Europe) (En,De,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02693") { // GZSZ Quiz (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02697") { // Pool Academy (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02700") { // Need for Speed - Porsche 2000 (Europe) (Fr,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02702") { // Primera Division Stars (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02704") { // UEFA Euro 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02705") { // UEFA Euro 2000 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02706") { // UEFA Euro 2000 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02707") { // UEFA Euro 2000 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02708") { // UEFA Euro 2000 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02764") { // All Star Tennis 2000 (Europe) (En,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02765") { // All Star Tennis 2000 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02766") { // Cochons de Guerre, Les (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02767") { // Frontschweine (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02768") { // Marranos en Guerra (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02769") { // Hogs of War - Nati per Soffritto (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02806") { // UEFA Challenge (Europe) (En,Fr,De,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02807") { // UEFA Challenge (Europe) (Fr,Es,It,Pt)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02808") { // Beach Volleyball (Europe) (En,Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02823") { // ECW Anarchy Rulz (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02825") { // Catan - Die erste Insel (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02849") { // Rampage - Through Time (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02853") { // Frogger 2 - Swampy's Revenge (Europe) (En,Fr,De,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02854") { // Breakout - A Story of Bat Meets Ball...! (Europe) (En,Fr,De,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02857") { // Sydney 2000 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02858") { // Sydney 2000 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02859") { // Sydney 2000 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02860") { // Sydney 2000 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02861") { // Sydney 2000 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02886") { // SLES-02886 (Spider-Man (Europe))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-02887") { // SLES-02887 (Spider-Man (France))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-02888") { // SLES-02888 (Spider-Man (Germany))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-02889") { // SLES-02889 (Spider-Man (Italy))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-02890") { // SLES-02890 (Spider-Man (Spain))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-02908") { // SLES-02908 (Tony Hawk's Pro Skater 2 (Europe, Australia))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-02909") { // SLES-02909 (Tony Hawk's Pro Skater 2 (France))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-02910") { // SLES-02910 (Tony Hawk's Pro Skater 2 (Germany))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-02918") { // Vegas Casino (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02948") { // Chris Kamara's Street Soccer (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02950") { // California Watersports (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-02988") { // Who Wants to Be a Millionaire (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03063") { // F.A. Premier League Stars 2001, The (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03064") { // LNF Stars 2001 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03065") { // Bundesliga Stars 2001 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03067") { // Madden NFL 2001 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03069") { // ECW Anarchy Rulz (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03082") { // European Super League (Europe) (En,Fr,De,Es,It,Pt)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03084") { // Inspector Gadget - Gadget's Crazy Maze (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03128") { // NBA Live 2001 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03129") { // NBA Live 2001 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03130") { // NBA Live 2001 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03131") { // NBA Live 2001 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03132") { // NBA Live 2001 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03139") { // NHL 2001 (Europe) (En,Sv,Fi)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03140") { // FIFA 2001 (Europe) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03141") { // FIFA 2001 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03142") { // FIFA 2001 (Germany) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03143") { // FIFA 2001 (Greece)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03144") { // FIFA 2001 (Israel)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03145") { // FIFA 2001 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03146") { // FIFA 2001 (Spain) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03148") { // Tiger Woods PGA Tour Golf (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03149") { // International Superstar Soccer (Europe) (Fr,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03154") { // NHL 2001 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03155") { // NHL 2001 (Europe) (Fr,Cs)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03206") { // Card Shark (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03210") { // Hunter, The (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03246") { // Monster Racer (Europe) (En,Fr,De,Es,It,Pt)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03251") { // WWF SmackDown! 2 - Know Your Role (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03262") { // UEFA Champions League - Season 2000-2001 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03280") { // UEFA Champions League - Season 2000-2001 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03281") { // UEFA Champions League - Season 2000-2001 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03282") { // UEFA Champions League - Season 2000-2001 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03283") { // UEFA Champions League - Season 2000-2001 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03321") { // ISS Pro Evolution 2 (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03322") { // ISS Pro Evolution 2 (Europe) (Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03327") { // Pro Body Boarding (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03328") { // Jetracer (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03329") { // Windsurfers Paradise (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03337") { // Tiger Woods USA Tour 2001 (Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03341") { // Wer wird Millionaer (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03362") { // NBA Hoopz (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03449") { // SLES-03449 (Roland Garros French Open 2001 (Europe) (En,Fr,De,Es,It))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-03480") { // Qui Veut Gagner des Millions (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03481") { // Quiere ser millonario (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03482") { // Hvem Vil Vaere Millionaer (Denmark)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03483") { // Vem Vill Bli Miljonaer (Sweden)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03488") { // David Beckham Soccer (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03499") { // You Don't Know Jack (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03511") { // Rageball (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03552") { // SLES-03552 (Breath of Fire IV (Europe))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLES-03579") { // Junior Sports Football (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03580") { // Junior Sports Football (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03581") { // Junior Sports Fussball (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03582") { // Chi Vuol Essere Miliardario (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03583") { // Who Wants to Be a Millionaire - Irish Edition (Ireland)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03584") { // Haluatko Miljonaariksi (Finland)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03585") { // Who Wants to Be a Millionaire - Australian Edition (Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03592") { // Who Wants to Be a Millionaire - Junior (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03593") { // Qui Veut Gagner des Millions - Junior (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03594") { // Wer wird Millionaer - Junior (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03595") { // Hot Wheels - Extreme Racing (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03642") { // Scrabble (Europe) (En,De,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03645") { // SLES-03645 (Tony Hawk's Pro Skater 3 (Europe))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-03646") { // SLES-03646 (Tony Hawk's Pro Skater 3 (France))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-03647") { // SLES-03647 (Tony Hawk's Pro Skater 3 (Germany))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-03662") { // SLES-03662 (Harry Potter and the Philosopher's Stone (Europe) (En,Fr,De))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03663") { // SLES-03663 (Harry Potter and the Philosopher's Stone (Europe) (Es,It,Pt))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03664") { // SLES-03664 (Harry Potter and the Philosopher's Stone (Scandinavia) (Sv,No,Fi))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03665") { // SLES-03665 (Harry Potter and the Philosopher's Stone (Europe) (En,Nl,Da))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03666") { // FIFA Football 2002 (Europe) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03668") { // FIFA Football 2002 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03669") { // FIFA Football 2002 (Germany) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03671") { // FIFA Football 2002 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03672") { // FIFA Football 2002 (Spain) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03682") { // David Beckham Soccer (Europe) (Fr,De,Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03718") { // NBA Live 2002 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03719") { // NBA Live 2002 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03720") { // NBA Live 2002 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03721") { // NBA Live 2002 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03722") { // NBA Live 2002 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03729") { // Cubix Robots for Everyone - Race 'n Robots (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03751") { // Scrabble (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03776") { // Sky Sports Football Quiz (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03779") { // Westlife - Fan-O-Mania (Europe) (Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03795") { // Pro Evolution Soccer (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03796") { // Pro Evolution Soccer (Europe) (Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03806") { // Westlife - Fan-O-Mania (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03808") { // Atari Anniversary Edition Redux (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03813") { // Monte Carlo Games Compendium (Europe) (Disc 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03830") { // 2002 FIFA World Cup (Europe) (En,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03831") { // 2002 FIFA World Cup (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03832") { // 2002 FIFA World Cup (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03833") { // 2002 FIFA World Cup (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03834") { // 2002 FIFA World Cup (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03856") { // Sky Sports Football Quiz - Season 02 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03868") { // Marcel Desailly Pro Football (France) (SLES-03868)
        gs->AddTrait(GameSettings::Trait::DisablePGXPCulling);
        return gs;
    }
    if (game_code == "SLES-03921") { // California Surfing (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03946") { // Pro Evolution Soccer 2 (Europe) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03954") { // SLES-03954 (Tony Hawk's Pro Skater 4 (Europe))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-03955") { // SLES-03955 (Tony Hawk's Pro Skater 4 (Germany))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-03956") { // SLES-03956 (Tony Hawk's Pro Skater 4 (France))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLES-03957") { // Pro Evolution Soccer 2 (Europe) (Es,It)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03963") { // All Star Tennis (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03968") { // NBA Live 2003 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03969") { // NBA Live 2003 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03970") { // NBA Live 2003 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03971") { // NBA Live 2003 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03972") { // SLES-03972 (Harry Potter and the Chamber of Secrets (Europe) (En,Fr,De))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03973") { // SLES-03973 (Harry Potter and the Chamber of Secrets (Europe) (Es,It,Pt))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03974") { // SLES-03974 (Harry Potter and the Chamber of Secrets (Europe) (En,Nl,Da))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03975") { // SLES-03975 (Harry Potter and the Chamber of Secrets (Scandinavia) (En,Sv,No))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03976") { // SLES-03976 (Harry Potter ja Salaisuuksien Kammio (Finland) (En,Fi))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-03977") { // FIFA Football 2003 (Europe) (En,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03978") { // FIFA Football 2003 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03979") { // FIFA Football 2003 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03980") { // FIFA Football 2003 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03981") { // FIFA Football 2003 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03982") { // NBA Live 2003 (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-03989") { // Dinomaster Party (Europe) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04047") { // Football Madness (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04060") { // All Star Watersports (Europe)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04104") { // Buttsubushi (Europe, Australia)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04115") { // FIFA Football 2004 (Europe) (En,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04116") { // FIFA Football 2004 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04117") { // FIFA Football 2004 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04118") { // FIFA Football 2004 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04119") { // FIFA Football 2004 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04165") { // FIFA Football 2005 (Europe) (En,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04166") { // FIFA Football 2005 (France)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04167") { // FIFA Football 2005 (Italy)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04168") { // FIFA Football 2005 (Germany)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-04169") { // FIFA Football 2005 (Spain)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-10584") { // SLES-10584 (Star Wars - Rebel Assault II - The Hidden Empire (Germany) (Disc 2))
        gs->gpu_max_run_ahead = 1;
        gs->dma_max_slice_ticks = 200;
        return gs;
    }
    if (game_code == "SLES-10643") { // SLES-10643 (Star Wars - Rebel Assault II - The Hidden Empire (Italy) (Disc 2))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLES-10644") { // SLES-10644 (Star Wars - Rebel Assault II - The Hidden Empire (Spain) (Disc 2))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLES-10654") { // SLES-10654 (Star Wars - Rebel Assault II - The Hidden Empire (Europe) (Disc 2))
        gs->gpu_max_run_ahead = 1;
        gs->dma_max_slice_ticks = 200;
        return gs;
    }
    if (game_code == "SLES-10656") { // SLES-10656 (Star Wars - Rebel Assault II - The Hidden Empire (France) (Disc 2))
        gs->gpu_max_run_ahead = 1;
        gs->dma_max_slice_ticks = 200;
        return gs;
    }
    if (game_code == "SLES-11436") { // Rival Schools - United by Fate (Europe) (Disc 2) (Arcade Disc)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLES-12397") { // SLES-12397 (Grandia (Europe) (Disc 2))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-12398") { // SLES-12398 (Grandia (France) (Disc 2))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-12399") { // SLES-12399 (Grandia (Germany) (Disc 2))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLES-13813") { // Monte Carlo Games Compendium (Europe) (Disc 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-80173") { // SLPM-80173 (Croc! Pau-Pau Island (Japan) (Demo))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPM-80297") { // SLPM-80297 (Grandia - Prologue (Japan) (Demo))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPM-80473") { // SLPM-80473 (Croc Adventure (Japan) (Demo))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPM-84013") { // SLPM-84013 (Harry Potter to Kenja no Ishi (Japan) (Coca-Cola Kenshouhin))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPM-86002") { // Hyper Olympic in Atlanta (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86011") { // NBA Power Dunkers 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86016") { // Paro Wars (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86034") { // Poitters' Point (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86044") { // Break Point (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86056" || game_code == "SLPM-86132") { // Hyper Olympic in Nagano (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86060") { // NBA Power Dunkers 3 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86061") { // Poitter's Point 2 - Sodom no Inbou (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86063") { // Noon (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86078") { // Actua Ice Hockey (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86080") { // Junclassic C.C. & Rope Club (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86086") { // SLPM-86086 (World Soccer Jikkyou Winning Eleven 3 - World Cup France '98 (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPM-86120") { // Itadaki Street - Gorgeous King (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86123") { // Bishi Bashi Special (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86170" || game_code == "SLPS-01090") { // Soulmaster (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86176") { // NBA Power Dunkers 4 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86192") { // SLPM-86192 (Silent Hill (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPM-86193") { // NHL Blades of Steel 2000 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86223") { // Culdcept - Expansion (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86240") { // SuperLite 1500 Series - Tenant Wars Alpha - SuperLite 1500 Version (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86259") { // SuperLite 1500 Series - Ano Ko Doko no Ko - Endless Season (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86269" || game_code == "SLPM-86270") { // Little Lovers - She So Game
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86272") { // Rakugaki Showtime (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86276") { // SuperLite 1500 Series - Pangaea (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86291") { // World Soccer Jikkyou Winning Eleven 4 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86297") { // SuperLite 1500 Series - Game de Seishun (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86310") { // SLPM-86310 (Croc Adventure (Japan))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPM-86317") { // Jikkyou J.League 1999 - Perfect Striker (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86365") { // SuperLite 1500 Series - Super Casino Special (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86392") { // Paro Wars [Konami the Best]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86397") { // NBA Power Dunkers 5 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86400") { // SuperLite 1500 Series - Battle Sugoroku the Hunter - A.R.0062 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86403") { // Umapoly (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86429") { // SLPM-86429 (Tony Hawk's Pro Skater (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLPM-86442") { // SuperLite 1500 Series - Tower Dream 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86464") { // Jikkyou Golf Master 2000 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86482") { // Ganbare! Nippon! Olympic 2000 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86487") { // Wu-Tang Shaolin Style
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86538") { // J.League Jikkyou Winning Eleven 2000 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86539") { // Bishi Bashi Special 3 - Step Champ (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86541") { // Love Game's - Wai Wai Tennis (Japan) (Major Wave)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86543") { // Egg (Japan) (Major Wave)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86544") { // Wai Wai Jansou (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86584") { // Tenkuu no Restaurant (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86590") { // Princess Maker - Go! Go! Princess (Japan) (Best Wing 2800)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86600") { // World Soccer Jikkyou Winning Eleven 2000 - U-23 Medal e no Chousen (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86617" || game_code == "SLPS-00237") { // Champion Wrestler - Jikkyou Live (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86620") { // Super Football Champ [Taito 2000 Series]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86621" || game_code == "SLPS-91451") { // Kero Kero King (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86626") { // Sydney 2000 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86643") { // Zipangu-jima - Unmei wa Saikoro ga Kimeru! (Japan) (Major Wave)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86651") { // Hunter x Hunter - Maboroshi no Greed Island (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86657") { // Wai Wai Trump Taisen (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86658") { // Culdcept - Expansion Plus (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86664") { // Tokoro-san no Daifugou
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86668") { // J.League Jikkyou Winning Eleven 2000 2nd (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86696") { // Wai Wai 3-nin Uchi Mahjong (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86713") { // Simple 1500 Series Vol. 54 - The Volleyball - Break Volley Plus (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86714") { // Simple 1500 Series Vol. 55 - The Darts (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86734") { // Tenkuu no Restaurant - Hello! Project Ver. (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86736") { // Jikkyou Golf Master 2000 (Japan) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86739") { // SLPM-86739 (Spider-Man (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPM-86750" || game_code == "SLPS-02120") { // Shiritsu Justice Gakuen - Nekketsu Seishun Nikki 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLPM-86751") { // SLPM-86751 (Tony Hawk's Pro Skater 2 (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLPM-86757") { // Little Lovers - She So Game (Japan) (Disc 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86758") { // Little Lovers - She So Game (Japan) (Disc 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86761") { // Simple 1500 Series Vol. 60 - The Table Hockey (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86799") { // SuperLite Gold Series - Minna no Mahjong (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86814" || game_code == "SLPS-01701") { // Capcom Generation - Dai-4-shuu Kokou no Eiyuu (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86820") { // Salaryman Champ - Tatakau Salaryman (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86824") { // Tokoro-san no Daifugou (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86825") { // Bishi Bashi Special [Konami The Best]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86829") { // Hunter X Hunter - Maboroshi no Greed Island [Konami the Best]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86835") { // J.League Jikkyou Winning Eleven 2001 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86842") { // Simple 1500 Series Vol. 65 - The Golf (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86844" || game_code == "SLPS-01717") { // Bomberman (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86864") { // Simple 1500 Series Vol. 67 - The Soccer - Dynamite Soccer 1500 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86868") { // Simple 1500 Series Vol. 69 - The Putter Golf (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86871") { // Simple 1500 Series Vol. 72 - The Beach Volley (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86888") { // Momotarou Matsuri - Ishikawa Rokuemon no Maki (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86899") { // Love Game's - Wai Wai Tennis Plus (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86908") { // DX Hyakunin Isshu (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86915") { // Simple 1500 Series Vol. 77 - The Suiei (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86943") { // SLPM-86943 (Tony Hawk's Pro Skater (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLPM-86944") { // Wu-Tang - Shaolin Style (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86950" || game_code == "SLPM-86690") { // Kinniku Banzuke Vol. 3 - Saikyou no Challenger Tanjou! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86963") { // Game of Life, The - DX Jinsei Game IV (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-86989") { // Oni Taiji!!, The - Mezase! Nidaime Momotarou (Japan) (Major Wave)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87015") { // Mini-Moni. Dice de Pyon! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87017") { // Simple 1500 Series Vol. 86 - The Onigokko (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87018") { // Palm Town (Japan) (Major Wave)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87032" || game_code == "SLPM-87347") { // Momotarou Dentetsu V (Japan) (Rev 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87056") { // World Soccer Winning Eleven 2002 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87080" || game_code == "SLPM-87364") { // Bomberman Land (Japan) (Rev 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87089") { // Pop'n Music 6 (Japan) (SLPM-87089)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLPM-87097" || game_code == "SLPS-02282") { // Quiz Darake no Jinsei Game - Un to Atama de Daifugou! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87098" || game_code == "SLPS-02469") { // Game of Life, The - DX Jinsei Game III (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87133") { // DX Monopoly [The Best Takaramono]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87135") { // Super Gals! Kotobuki Ran Special - Ikemen Get You Gals Party (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87156") { // Quiz Darake No Jinsei Game Dai-2-Kai!
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87159") { // SLPM-87159 (Breath of Fire IV - Utsurowazaru Mono (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPM-87187") { // Game of Life, The - DX Jinsei Game V (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87195") { // Mini-Moni. Step Pyon Pyon Pyon (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87201") { // Mini Moni - Dice de Pyon! [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87205") { // Hunter X Hunter - Maboroshi no Greed Island [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87206") { // Bishi Bashi Special [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87208") { // Bishi Bashi Special 3 - Step Champ [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87241" || game_code == "SLPM-87361") { // Harukanaru Toki no Naka de - Banjou Yuugi (Japan) (Premium Box)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87242") { // Harukanaru Toki no Naka de - Banjou Yuugi (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87251") { // Shin DX Okuman Chouja Game - Tsukutte! Utte! Oomouke! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87257") { // Momotarou Dentetsu 7 [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87285") { // DX Jinsei Game IV - The Game of Life [The Best Takaramono]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87316" || game_code == "SLPS-03056") { // Oshigoto-shiki Jinsei Game - Mezase Shokugyou King (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87340") { // Combat Choro Q [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87344") { // DX Okuman Chouja Game II [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87345") { // DX Shachou Game [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87346") { // Dai-2-kai! Quiz Darake no Jinsei Game (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87348") { // DX Jinsei Game V [The Best Takaramono] (aka DX Jinsei Game V - The Game of Life [The Best Takaramono])
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87351") { // Harukanaru Toki no naka de - Banue Yuugi [Koei Teiban Series]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87363") { // Capcom Retro Game Collection Vol. 4
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87368") { // DX Jinsei Game V [PSone Books] (aka DX Jinsei Game V - The Game of Life [PSone Books])
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPM-87395") { // SLPM-87395 (Chrono Cross (Japan) (Disc 1))
        gs->dma_max_slice_ticks = 100;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->dma_halt_ticks = 150;
        return gs;
    }
    if (game_code == "SLPM-87396") { // SLPM-87396 (Chrono Cross (Japan) (Disc 2))
        gs->dma_halt_ticks = 150;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLPS-00025") { // SLPS-00025 (Toushinden (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-00089") { // Oni Taiji!!, The - Mezase! Nidaime Momotarou (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00115") { // Kuma no Pooh-tarou - Sora wa Pink da! Zen'in Shuugou!! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00127") { // Striker - World Cup Premiere Stage (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00155" || game_code == "SLPS-91025") { // Game of Life, The - DX Jinsei Game (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00158") { // Bakushou!! All Yoshimoto Quiz-ou Kettei-sen DX (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00164") { // Tetsudou-ou '96 - Iku ze Okuman Chouja!! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00188") { // NBA Power Dunkers (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00199") { // NBA Jam - Tournament Edition (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00202") { // Taiketsu Rumiizu! Meruhen Land (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00221") { // NFL Quarterback Club '96
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00236") { // Uchuu Goushouden - Bakuretsu Akindo (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00241") { // America Oudan Ultra Quiz (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00267") { // SLPS-00267 (Deadheat Road (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-00270") { // Galaxian^3 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00275") { // SLPS-00275 (Defcon 5 (Japan))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLPS-00278") { // Hyper Final Match Tennis (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00298") { // Actua Golf (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00299") { // Daisenryaku - Player's Spirit (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00301") { // J.League Virtual Stadium '96 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00308") { // SLPS-00308 (Doom (Japan))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLPS-00321" || game_code == "SLPS-91036") { // Tetris X (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00359") { // Meru Purana (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00360") { // SLPS-00360 (Super Pang Collection (Japan))
        gs->display_active_start_offset = -62;
        gs->display_active_end_offset = 72;
        return gs;
    }
    if (game_code == "SLPS-00381") { // Shin Fortune Quest - Shokutaku no Kishi-tachi (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00382") { // Shin Fortune Quest - Shokutaku no Kishi-tachi
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00389") { // NBA Live 96 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00426") { // Magic Johnson to Kareem Abdul-Jabbar no Slam 'n Jam '96 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00435") { // SLPS-00435 (Megatudo 2096 (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-00450" || game_code == "SLPS-91053" || game_code == "SLPS-91407") { // Smash Court (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00465") { // Honoo no 15 Shumoku - Atlanta Olympics (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00467") { // Super Casino Special (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00469") { // V-Tennis 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00523") { // Olympic Soccer (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00531") { // Proof Club (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00569") { // Super Football Champ (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00594") { // Sampras Extreme Tennis (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00595") { // NHL Powerplay '96 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00607") { // Pitball (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00610") { // Street Racer Extra (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00615") { // Gritz - The Pyramid Adventure (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00622") { // Kyuu Bakukku (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00623" || game_code == "SLPS-91046") { // DX Okuman Chouja Game - The Money Battle (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00626" || game_code == "SLPS-91066") { // Goo-Cho de Park - Theme Park Monogatari (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00637") { // Shin Nihon Pro Wrestling - Toukon Retsuden 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00638") { // SLPS-00638 (Star Wars - Rebel Assault II - The Hidden Empire (Japan) (Disc 1))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLPS-00639") { // SLPS-00639 (Star Wars - Rebel Assault II - The Hidden Empire (Japan) (Disc 2))
        gs->gpu_max_run_ahead = 1;
        gs->dma_max_slice_ticks = 200;
        return gs;
    }
    if (game_code == "SLPS-00648") { // Econo Kids - Ta ga Tame ni Kane wa Naru (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00652") { // Ultraman Zearth (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00658") { // Nippon Golf Kyoukai Kanshuu - Double Eagle
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00682") { // Triple Play 97 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00686") { // Love Game's - Wai Wai Tennis
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00695") { // WWF In Your House (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00697") { // Space Jam (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00699") { // NBA Jam Extreme (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-00712") { // SLPS-00712 (Tenga Seiha (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-00727") { // Final Doom (Japan) (SLPS-00727)
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLPS-00732") { // Las Vegas Dream 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00736") { // NBA Live 97 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00741" || game_code == "SLPS-01682") { // Monopoly (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00768") { // Naniwa no Akindo - Futte Nanbo no Saikoro Jinsei (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00821") { // Hi-Hou-Ou - Mou Omae to wa Kuchi Kikan!! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00832" || game_code == "SLPS-91115") { // Iwatobi Penguin Rocky x Hopper (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00858") { // Next King - Koi no Sennen Oukoku (Japan) (Genteiban)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00859") { // Next King - Koi no Sennen Oukoku (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00861") { // NHL 97 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00869") { // SLPS-00869 (Chou-Kousoku Gran Doll (Japan) (Disc 1) (Premium Edition))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLPS-00870") { // SLPS-00870 (Chou-Kousoku Gran Doll (Japan) (Disc 2) (Tokusei Premium Disc) (Premium Edition))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLPS-00878") { // FIFA Soccer 97 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00887") { // Triple Play 98 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00892") { // Virtual Bowling - Ten Pin Alley no Kiseki (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00899") { // Panzer Bandit (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00900") { // SLPS-00900 (Armored Core (Japan))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLPS-00915") { // Kaibutsu Para-Dice - Monster Paradise (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00918") { // Game of Life, The - DX Jinsei Game II (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-00935") { // SLPS-00935 (Chou-Kousoku Gran Doll (Japan))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLPS-00968") { // Battle Formation (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01006") { // Pro Wres Sengokuden - Hyper Tag Match (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01009") { // SLPS-01009 (Lagnacure (Japan, Asia))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLPS-01012") { // Tetsudou-ou 2 - Sekai Seifuku no Yabou!! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01025") { // Dare Devil Derby 3D (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01026") { // Cu-On-Pa (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01034") { // Fantastic Four (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01055") { // SLPS-01055 (Croc! Pau-Pau Island (Japan))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPS-01111") { // Micro Machines (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01113") { // Toushinden - Card Quest (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01121") { // Egg (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01155") { // Bomberman World (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01156") { // Momotarou Dentetsu 7 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01162") { // Panel Quiz Attack 25 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01166") { // Waku Waku Bowling (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01167") { // Tour Party - Sotsugyou Ryokou ni Ikou (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01173") { // Magical Zunou Power!! Party Selection (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01177") { // Kimagure My Baby - Musume no Sugoroku Seichouki (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01209") { // Blaze & Blade - Eternal Quest (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01211") { // Time Bokan Series: Bokan desu yo (SLPS-01211)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLPS-01215") { // Dengeki Construction - Ochigee Yarou ze! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01240") { // Shiritsu Justice Gakuen - Legion of Heroes (Japan) (Disc 1) (Evolution Disc)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01241") { // Shiritsu Justice Gakuen - Legion of Heroes (Japan) (Disc 2) (Arcade Disc)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01242") { // Motteke Tamago with Ganbare! Kamonohashi (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01243") { // Tenant Wars (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01264") { // Suchie-Pai Adventure - Doki Doki Nightmare (Japan) (Disc 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01265") { // Suchie-Pai Adventure - Doki Doki Nightmare (Japan) (Disc 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01268" || game_code == "SLPS-02057" || game_code == "SLPS-91417") { // Great Rugby Jikkyou '98 - World Cup e no Michi (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01283") { // Iwatobi Penguin Rocky x Hopper 2 - Tantei Monogatari (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01287") { // Denpa Shounen-teki Game (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01296") { // NBA Live 98 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01303") { // Tennis Arena (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01306") { // Game de Seishun
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01314") { // Shin Nihon Pro Wrestling - Toukon Retsuden 3 (Japan) (Antonio Inoki Intai Kinen Genteiban)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01361") { // Hit Back (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01366") { // Shin Nihon Pro Wrestling - Toukon Retsuden 3 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01379") { // World Pro Tennis '98 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01383") { // FIFA - Road to World Cup 98 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01389" || game_code == "SLPS-02687") { // World League Soccer (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01399") { // Frogger (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01414") { // Dynamite Soccer 98 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01434") { // SLPS-01434 (3D Kakutou Tkool (Japan))
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLPS-01438") { // Arcana Senki Ludo (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01440" || game_code == "SLPS-02225") { // Trump Shiyou yo! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01473") { // Sentimental Journey (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01483") { // ZigZagBall (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01486") { // Carom Shot 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01505") { // Princess Maker - Go!Go! Princess
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01522") { // Ano Ko Doko no Ko (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01546") { // Rami-chan no Ooedo Sugoroku - Keiou Yuugekitai Gaiden (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01557") { // Duke Nukem - Total Meltdown (Japan) (SLPS-01557)
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLPS-01559") { // Dokapon! Ikari no Tekken (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01560") { // SD Gundam - GGeneration (Japan) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01561") { // SD Gundam - GGeneration (Premium Disc) (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01567") { // Captain Commando (Japan)
        gs->display_active_start_offset = -62;
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->display_active_end_offset = 51;
        return gs;
    }
    if (game_code == "SLPS-01576") { // Blaze & Blade Busters (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01586" || game_code == "SLPS-02566") { // DX Okuman Chouja Game II - The Money Battle (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01621") { // Triple Play 99 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01624") { // Granew-tou! Daibouken (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01647") { // Love Game's - Wai Wai Tennis (Japan) (Service Price-ban)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01667" || game_code == "SLPS-02796") { // Nihon Pro Golf Kyoukai Kanshuu - Double Eagle (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01693") { // Smash Court 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01695" || game_code == "SLPS-02346" || game_code == "SLPS-02356" || game_code == "SLPS-02359" || game_code == "SLPS-02373" || game_code == "SLPS-02378") { // Waku Waku Volley (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01715") { // Missland 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01719") { // FIFA World Cup 98 - France 98 Soushuuhen (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01730") { // 100 Man Yen Quiz Hunter (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01740") { // Sakuma-shiki Jinsei Game (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01762") { // SLPS-01762 (Pepsiman (Japan))
        gs->AddTrait(GameSettings::Trait::DisablePGXPCulling);
        return gs;
    }
    if (game_code == "SLPS-01774") { // SLPS-01774 (Next Tetris, The (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-01789") { // Tower Dream 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01802" || game_code == "SLPS-91484") { // America Oudan Ultra Quiz (Japan) (Fukkokuban)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01820") { // Palm Town (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01849") { // Zen Nihon Pro Wres - Ouja no Tamashii (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01904") { // Combat Choro Q (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01937") { // Enomoto Kanako no Boke Shindan Game (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01962") { // All Star Tennis '99 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-01983") { // Blackjack vs. Matsuda Jun (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02011") { // Doukyuu re-mix - Billiards Multiple (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02012") { // Tiger Woods 99 PGA Tour Golf (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02033") { // NBA Live 99 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02065") { // Fire Pro Wrestling G (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02075") { // GaiaMaster - Kamigami no Board Game (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02105" || game_code == "SLPS-03071") { // DX Shachou Game (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02124") { // SLPS-02124 (Grandia (Japan) (Disc 1))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPS-02125") { // SLPS-02125 (Grandia (Japan) (Disc 2))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPS-02135") { // Perfect Performer - The Yellow Monkey (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02168") { // Lord of Fist (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02189") { // Quiz Chara-Oke Don! Toei Tokusatsu Hero Part 1 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02200") { // SD Gundam - GGeneration-0 (Japan) (Disc 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02201") { // SD Gundam - GGeneration-0 (Japan) (Disc 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02202") { // Kidou Senshi Gundam - Gihren no Yabou - Zeon no Keifu - Kimitsu Eizou Disc Tokubetsu-hen (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02228") { // Simple 1500 Series Vol. 26 - The Tennis (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02260") { // Zipangu-jima - Unmei wa Saikoro ga Kimeru! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02309") { // FIFA 99 - Europe League Soccer (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02310") { // Quiz Chara-Oke Don! Toei Tokusatsu Hero Part 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02361") { // SLPS-02361 (Touge Max G (Japan))
        gs->AddTrait(GameSettings::Trait::ForcePGXPVertexCache);
        return gs;
    }
    if (game_code == "SLPS-02364") { // SLPS-02364 (Chrono Cross (Japan) (Disc 1))
        gs->dma_max_slice_ticks = 100;
        gs->dma_halt_ticks = 150;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-02365") { // SLPS-02365 (Chrono Cross (Japan) (Disc 2))
        gs->dma_max_slice_ticks = 100;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->dma_halt_ticks = 150;
        return gs;
    }
    if (game_code == "SLPS-02376") { // SLPS-02376 (Little Princess - Marl Oukoku no Ningyou-hime 2 (Japan))
        gs->gpu_max_run_ahead = 1;
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLPS-02456") { // Momotarou Dentetsu V (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02457") { // Battle Bombee 2 - Sukkiri Momoaji (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02458") { // Momotarou Dentetsu V (Japan) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02491") { // Monster Punish (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02510") { // Love Game's - Wai Wai Tennis 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02516" || game_code == "SLPS-91467") { // V-Rally - Championship Edition 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02552") { // Magical Zunou Power!! Party Selection (Vap Best Thanks 1800)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02554") { // Dynamite Soccer 2000 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02567") { // Tour Party - Sotsugyou Ryokou ni Ikou [The Best Takaramono]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02603") { // NBA Live 2000 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02612") { // Trump Shiyou yo! (Japan) (Fukkokuban)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02653") { // Monster Farm Battle Card (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02675") { // FIFA 2000 - Europe League Soccer (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02701") { // SLPS-02701 (Next Tetris, The (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-02710") { // Art Camion - Sugorokuden (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02728") { // SLPS-02728 (Breath of Fire IV - Utsurowazaru Mono (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-02731") { // Aquarian Age - Tokyo Wars (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02751" || game_code == "SLPS-00263") { // Athena no Kateiban - Family Games (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02756") { // Simple 1500 Series Vol. 30 - The Basket - 1 on 1 Plus (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02777") { // SLPS-02777 (Chrono Cross (Japan) (Disc 1))
        gs->dma_halt_ticks = 150;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLPS-02778") { // SLPS-02778 (Chrono Cross (Japan) (Disc 2))
        gs->dma_max_slice_ticks = 100;
        gs->dma_halt_ticks = 150;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLPS-02797") { // Dioramos (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02817") { // Fire Pro Wrestling G (Japan) (Spike Library)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02833") { // SLPS-02833 (Lagnacure (Japan) (Artdink Best Choice))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLPS-02851" || game_code == "SLPS-91429") { // Denkousekka Micro Runner - Maniac Hakase no Hisaku (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02852") { // WTC World Touring Car Championship (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02857") { // 20 Seiki Striker Retsuden (Rerelease)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02877") { // Shinobi no Roku (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02878") { // SLPS-02878 (Colin McRae - The Rally 02 (Japan))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLPS-02885") { // Exciting Pro Wres (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02900" || game_code == "SLPS-02912") { // SD Gundam - GGeneration-F (Japan) (Disc 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02901" || game_code == "SLPS-02913") { // SD Gundam - GGeneration-F (Japan) (Disc 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02902" || game_code == "SLPS-02914") { // SD Gundam - GGeneration-F (Japan) (Disc 3)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02903") { // SD Gundam - GGeneration-F (Japan) (Disc 4) (Premium Disc) (Limited Edition)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02909") { // Simple 1500 Series Vol. 34 - The Quiz Bangumi (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02915") { // SD Gundam - GGeneration-F (Japan) (Disc 4) (Premium Disc)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02934" || game_code == "SLPS-91428") { // Zen Nihon Pro Wres - Ouja no Tamashii (Japan) (Spike Library)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02943") { // DX Monopoly (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-02983") { // Love Game's - Wai Wai Tennis 2 (Japan) (Value 1500)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03000") { // Ms. Pac-Man Maze Madness (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03001") { // Smash Court 3 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03002") { // Bomberman Land (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03045") { // Tales of Eternia (Japan) (Disc 1) (Premium Box)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03046") { // Tales of Eternia (Japan) (Disc 2) (Premium Box)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03047") { // Tales of Eternia (Japan) (Disc 3) (Premium Box)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03049") { // Naniwa Kinyuudou - Aoki Yuji no Seken Munazanyou (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03050" || game_code == "SLPS-91247") { // Tales of Eternia (Japan) (Disc 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03051" || game_code == "SLPS-91248") { // Tales of Eternia (Japan) (Disc 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03052" || game_code == "SLPS-91249") { // Tales of Eternia (Japan) (Disc 3)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03070") { // Combat Choro Q [The Best Takaramono]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03098") { // Youchien Gaiden - Karei naru Casino Club - Double Draw (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03114") { // Puyo Puyo Box (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03122" || game_code == "SLPS-91497") { // Exciting Pro Wres 2 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03162") { // Buttsubushi (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03195") { // SD Gundam - GGeneration-F.I.F (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03206") { // SD Gundam - GGeneration-0 (Japan) (Disc 1) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03207") { // SD Gundam - GGeneration-0 (Japan) (Disc 2) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03250") { // Doko Demo Hamster 4 - Doki Doki Sugoroku Daibouken! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03266") { // Hamster Club-i (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03303") { // WTC - World Touring Championship [Spike Library #009]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03321") { // Motto Trump Shiyou yo! i-Mode de Grand Prix (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03336") { // Mr. Driller G (Japan) (SLPS-03336)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLPS-03355") { // SLPS-03355 (Harry Potter to Kenja no Ishi (Japan))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPS-03362") { // Simple Character 2000 Series Vol. 05 - High School Kimengumi - The Table Hockey (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03364") { // Quiz$Millionaire (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03384") { // Nice Price Series Vol. 06 - Quiz de Battle (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03433") { // Klonoa Beach Volley - Saikyou Team Kettei-sen! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03436") { // Dynamite Soccer 2002 (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03458") { // Simple Character 2000 Series Vol. 11 - Meitantei Conan - The Board Game (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03460") { // Pooh-san no Minna de Mori no Daikyousou! (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03491") { // Minnya de Ghost Hunter (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03492") { // SLPS-03492 (Harry Potter to Himitsu no Heya (Japan))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPS-03494") { // Quiz$Millionaire - Waku Waku Party (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03553") { // Naruto - Shinobi no Sato no Jintori Gassen (Japan)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03575") { // Dynamite Soccer 2004 Final (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-03581") { // SLPS-03581 (Armored Core (Japan) (Rev 1))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLPS-91064") { // SLPS-91064 (Armored Core (Japan) (Rev 1))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLPS-91065") { // SD Gundam - GCentury (Japan) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91149") { // Bomberman World (Japan) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91150") { // FIFA - Road to World Cup 98 - World Cup e no Michi [PlayStation the Best]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91178") { // Daisenryaku - Player's Spirit (Japan) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91190") { // Dokapon! Ikari no Tekken (Japan) (Rev 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91205") { // SLPS-91205 (Grandia (Japan) (Disc 1))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPS-91206") { // SLPS-91206 (Grandia (Japan) (Disc 2))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLPS-91416") { // 20-seiki Striker Retsuden - The 20th Century's Real Strikers (Japan)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91450") { // Doukyu Re-Mix Billiard Multiple [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91452") { // Tenkuu no Restaurant (Japan) (Rev 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91464") { // SLPS-91464 (Chrono Cross (Japan) (Disc 1))
        gs->dma_max_slice_ticks = 100;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->dma_halt_ticks = 150;
        return gs;
    }
    if (game_code == "SLPS-91465") { // SLPS-91465 (Chrono Cross (Japan) (Disc 2))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->dma_halt_ticks = 150;
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLPS-91476") { // Guucho de Park - Theme Park Monogatari [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91488") { // WTC - World Touring Championship [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91515") { // Quiz$Millionaire (Japan) (PSone Books)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLPS-91529") { // Quiz $ Millionaire - Waku Waku Party [PSOne Books]
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00002") { // NBA Jam - Tournament Edition (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00009") { // SLUS-00009 (Defcon 5 - Peace Has a Price... (USA))
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLUS-00011") { // NFL Quarterback Club 97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00018") { // Madden NFL 97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00022") { // Slam 'n Jam '96 featuring Magic & Kareem (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLUS-00030") { // NHL 97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00038") { // FIFA Soccer 96 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00048") { // NBA in the Zone (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00060") { // NBA Live 96 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00077") { // Doom (USA) (Rev 1) (SLUS-00077)
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        return gs;
    }
    if (game_code == "SLUS-00099") { // Street Racer (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00142") { // NCAA Basketball Final Four 97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00146") { // Pitball (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00147") { // Wayne Gretzky's 3D Hockey '98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00148") { // Olympic Summer Games (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00156") { // Olympic Soccer (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00183") { // SLUS-00183 (Zero Divide (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLUS-00196") { // College Slam (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00198") { // VR Golf '97 (USA) (En,Fr)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00208") { // SLUS-00208 (Buster Bros. Collection (USA))
        gs->display_active_end_offset = 72;
        gs->display_active_start_offset = -62;
        return gs;
    }
    if (game_code == "SLUS-00210") { // Striker 96 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00219") { // Blast Chamber (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00227") { // NHL Powerplay '96 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00232") { // SLUS-00232 (Pandemonium! (USA))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLUS-00237") { // Triple Play 97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00238") { // International Track & Field (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00243") { // Space Jam (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00246") { // WWF In Your House (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00262") { // Syndicate Wars (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00267") { // NBA Live 97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00269") { // FIFA Soccer 97 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00282") { // SLUS-00282 (Red Asphalt (USA))
        gs->gpu_max_run_ahead = 1;
        gs->dma_max_slice_ticks = 200;
        return gs;
    }
    if (game_code == "SLUS-00292") { // SLUS-00292 (Suikoden (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLUS-00294") { // NBA in the Zone 2 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00297") { // SLUS-00297 (Star Wars - Dark Forces (USA))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLUS-00300") { // Dare Devil Derby 3D (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00327") { // NHL Open Ice - 2 on 2 Challenge (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00329") { // NBA Hangtime (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00331") { // SLUS-00331 (Final Doom (USA))
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLUS-00337") { // True Pinball (USA) (SLUS-00337)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLUS-00348") { // Hexen (SLUS-00348)
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLUS-00355") { // Duke Nukem - Total Meltdown (USA) (SLUS-00355)
        gs->AddTrait(GameSettings::Trait::DisablePGXP);
        gs->AddTrait(GameSettings::Trait::DisableUpscaling);
        return gs;
    }
    if (game_code == "SLUS-00377") { // Ten Pin Alley (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00381") { // SLUS-00381 (Star Wars - Rebel Assault II - The Hidden Empire (USA) (Disc 1))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLUS-00386") { // SLUS-00386 (Star Wars - Rebel Assault II - The Hidden Empire (USA) (Disc 2))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLUS-00388") { // NBA Jam Extreme (USA)
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00391") { // NHL Breakaway 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00395") { // Fantastic Four (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00445") { // NBA in the Zone '98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00449") { // Arcade's Greatest Hits - The Atari Collection 2 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00465") { // Triple Play 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00486") { // Poy Poy (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00492") { // NBA Fastbreak '98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00495") { // WWF War Zone (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00500") { // Jimmy Johnson's VR Football '98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00506") { // Frogger (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00507") { // Monopoly (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00514") { // NCAA Football 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00516") { // Madden NFL 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00519") { // NHL 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00520") { // FIFA - Road to World Cup 98 (USA) (En,Fr,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00523") { // NBA Live 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00524") { // SLUS-00524 (Road Rash 3D (USA))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLUS-00526") { // March Madness '98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00528") { // NHL Powerplay 98 (USA) (En,Fr,De)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00530") { // SLUS-00530 (Croc - Legend of the Gobbos (USA))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLUS-00547") { // Adidas Power Soccer 98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLUS-00558") { // Shipwreckers! (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00559") { // Micro Machines V3 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00571") { // Brunswick Circuit Pro Bowling (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00591") { // Nagano Winter Olympics '98 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00596") { // Tennis Arena (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00616") { // Risk - The Game of Global Domination (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00618") { // Triple Play 99 (USA) (En,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00634") { // SLUS-00634 (Croc 2 (USA))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLUS-00635") { // FOX Sports Soccer '99 (USA) (En,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00636") { // FOX Sports Golf '99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00639") { // Pro Pinball - Timeshock! (USA) (SLUS-00639)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        return gs;
    }
    if (game_code == "SLUS-00644") { // World Cup 98 (USA)
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00656") { // Rat Attack! (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLUS-00657") { // VIVA Soccer
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00659") { // Backstreet Billiards (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00672") { // Devil Dice (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00674") { // SLUS-00674 (International Superstar Soccer Pro '98 (USA) (En,Fr,De,Es,It))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLUS-00680") { // Bomberman World (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00681") { // Rival Schools - United by Fate (USA) (Disc 1) (Arcade Disc)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00682") { // Jeopardy! (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00688") { // NCAA Football 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00692") { // S.C.A.R.S. (USA)
        gs->multitap_mode = MultitapMode::Port2Only;
        return gs;
    }
    if (game_code == "SLUS-00697") { // Circuit Breakers (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00707") { // SLUS-00707 (Silent Hill (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLUS-00729") { // Madden NFL 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00735") { // NHL 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00736") { // NBA Live 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00742") { // Rampage 2 - Universal Tour (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00757") { // Quake II (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00769") { // Game of Life, The (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00771") { // Rival Schools - United by Fate (USA) (Disc 2) (Evolution Disc)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00782") { // FIFA 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00785") { // Tiger Woods 99 PGA Tour Golf (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00791") { // NBA in the Zone '99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00805") { // NCAA March Madness 99 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00817") { // Pro 18 - World Tour Golf (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00825") { // NHL Blades of Steel 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00831") { // WWF Attitude (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00836") { // Vegas Games 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00856") { // Brunswick Circuit Pro Bowling 2 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00860") { // SLUS-00860 (Tony Hawk's Pro Skater (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLUS-00861") { // NFL Blitz 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00862") { // SLUS-00862 (Next Tetris, The (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLUS-00864") { // Ultimate 8 Ball (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00869") { // Team Buddies (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00870") { // SLUS-00870 (Formula One 99 (USA) (En,Fr,Es))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SLUS-00875") { // SLUS-00875 (Spider-Man (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLUS-00889" || game_code == "SLUS-80889") { // Pong - The Next Level (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00912") { // Destruction Derby Raw (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLUS-00925") { // NHL Championship 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00926") { // NBA Basketball 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00927") { // WWF SmackDown! (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00929") { // Wu-Tang - Shaolin Style (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00932") { // NCAA Football 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00948") { // NBA Showtime - NBA on NBC (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00952") { // Arcade Party Pak (USA)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00953") { // Viva Soccer (USA) (En,Fr,De,Es,It,Pt)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00955") { // Sled Storm (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00961") { // Madden NFL 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00963") { // WCW Mayhem (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00965") { // NHL 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00970") { // Gekido - Urban Fighters (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00987") { // International Track & Field 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00994") { // FIFA 2000 - Major League Soccer (USA) (En,De,Es,Nl,Sv)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00997") { // South Park - Chef's Luv Shack (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-00998") { // NBA Live 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01003") { // Need for Speed - V-Rally 2 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01004") { // CyberTiger (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01006") { // MTV Music Generator (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01014") { // ISS Pro Evolution (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01017") { // SLUS-01017 (Alundra 2 - A New Legend Begins (USA))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLUS-01018") { // Ms. Pac-Man Maze Madness (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01023") { // NCAA March Madness 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01028") { // NBA in the Zone 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01041") { // SLUS-01041 (Chrono Cross (USA) (Disc 1))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        gs->dma_halt_ticks = 150;
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLUS-01045") { // ECW Hardcore Revolution (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01053") { // Road Rash - Jailbreak (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01054") { // Tiger Woods PGA Tour 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01065") { // Rampage - Through Time (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01066") { // SLUS-01066 (Tony Hawk's Pro Skater 2 (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLUS-01078") { // Striker Pro 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01080") { // SLUS-01080 (Chrono Cross (USA) (Disc 2))
        gs->dma_max_slice_ticks = 100;
        gs->dma_halt_ticks = 150;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLUS-01089") { // Caesars Palace 2000 - Millennium Gold Edition (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01094") { // Backyard Soccer (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01104") { // Need for Speed - Porsche Unleashed (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01125") { // Kurt Warner's Arena Football Unleashed (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01129") { // FoxKids.com - Micro Maniacs Racing (USA)
        gs->multitap_mode = MultitapMode::BothPorts;
        return gs;
    }
    if (game_code == "SLUS-01130") { // Peter Jacobsen's Golden Tee Golf (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01134") { // SLUS-01134 (Formula One 2000 (USA))
        gs->AddTrait(GameSettings::Trait::ForceInterpreter);
        return gs;
    }
    if (game_code == "SLUS-01138") { // SLUS-01138 (Vampire Hunter D (USA))
        gs->dma_max_slice_ticks = 200;
        gs->gpu_max_run_ahead = 1;
        return gs;
    }
    if (game_code == "SLUS-01139") { // Jarrett & Labonte Stock Car Racing (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01146") { // NFL Blitz 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01169") { // ECW Anarchy Rulz (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01170") { // Breakout (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01172") { // Frogger 2 - Swampy's Revenge (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01173") { // Jeopardy! 2nd Edition (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01174") { // Wheel of Fortune - 2nd Edition (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01177") { // Sydney 2000 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01178") { // Monster Rancher Battle Card - Episode II (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01186") { // ESPN MLS Gamenight (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01189") { // Bomberman - Party Edition (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01195") { // Hogs of War (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01196") { // Power Spike - Pro Beach Volleyball (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01219") { // NCAA Football 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01222") { // SLUS-01222 (Colin McRae Rally 2.0 (USA) (En,Fr,Es))
        gs->display_active_end_offset = 68;
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        gs->display_active_start_offset = 64;
        return gs;
    }
    if (game_code == "SLUS-01234") { // WWF SmackDown! 2 - Know Your Role (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01241") { // Madden NFL 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01260") { // Pro Pinball - Big Race USA (USA) (SLUS-01260)
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        return gs;
    }
    if (game_code == "SLUS-01261") { // Pro Pinball - Fantastic Journey (USA) (SLUS-01261)
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLUS-01262") { // FIFA 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01264") { // NHL 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01267") { // Inspector Gadget - Gadget's Crazy Maze (USA) (En,Fr,De,Es,It,Nl)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01271") { // NBA Live 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01273") { // Tiger Woods PGA Tour Golf (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01293") { // Hot Wheels - Extreme Racing (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01320") { // NCAA March Madness 2001 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01323") { // SLUS-01323 (Armored Core (USA) (Reprint))
        gs->dma_max_slice_ticks = 100;
        return gs;
    }
    if (game_code == "SLUS-01324") { // SLUS-01324 (Breath of Fire IV (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerICache);
        return gs;
    }
    if (game_code == "SLUS-01331") { // NBA Hoopz (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01333") { // Board Game - Top Shop (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01335") { // Battle Hunter (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01348") { // Tennis (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01355") { // Tales of Destiny II (USA) (Disc 1)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01367") { // Tales of Destiny II (USA) (Disc 2)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01368") { // Tales of Destiny II (USA) (Disc 3)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01371") { // Putter Golf (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01402") { // Madden NFL 2002 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01408") { // FIFA Soccer 2002 (USA) (En,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01415") { // SLUS-01415 (Harry Potter and the Sorcerer's Stone (USA) (En,Fr,Es))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLUS-01416") { // NBA Live 2002 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01417") { // SLUS-01417 (Harry Potter and the Philosopher's Stone (Canada) (En,Fr,De))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLUS-01419") { // SLUS-01419 (Tony Hawk's Pro Skater 3 (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLUS-01422") { // Cubix Robots for Everyone - Race 'n Robots (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01427") { // Atari Anniversary Edition Redux (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01437") { // Disney's Pooh's Party Game - In Search of the Treasure (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01445") { // Power Play - Sports Trivia (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01449") { // 2002 FIFA World Cup (USA) (En,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01454") { // Family Card Games Fun Pack (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01455") { // David Beckham Soccer (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01461") { // Rageball (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01482") { // Madden NFL 2003 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01483") { // NBA Live 2003 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01485") { // SLUS-01485 (Tony Hawk's Pro Skater 4 (USA))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }
    if (game_code == "SLUS-01503") { // SLUS-01503 (Harry Potter and the Chamber of Secrets (USA) (En,Fr,Es))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLUS-01504") { // FIFA Soccer 2003 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01570") { // Madden NFL 2004 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01578") { // FIFA Soccer 2004 (USA) (En,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01584") { // Madden NFL 2005 (USA)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-01585") { // FIFA Soccer 2005 (USA) (En,Es)
        gs->multitap_mode = MultitapMode::Port1Only;
        return gs;
    }
    if (game_code == "SLUS-0381") { // SLUS-0381 (Star Wars - Rebel Assault II - The Hidden Empire (USA) (Disc 1))
        gs->gpu_max_run_ahead = 1;
        gs->dma_max_slice_ticks = 200;
        return gs;
    }
    if (game_code == "SLUS-90039") { // Pro Pinball - Timeshock! (USA) (Demo) (SLUS-90039)
        gs->AddTrait(GameSettings::Trait::ForceSoftwareRenderer);
        gs->AddTrait(GameSettings::Trait::ForceInterlacing);
        return gs;
    }
    if (game_code == "SLUS-90056") { // SLUS-90056 (Croc 2 (USA) (Demo))
        gs->AddTrait(GameSettings::Trait::ForcePGXPCPUMode);
        return gs;
    }
    if (game_code == "SLUS-90086") { // SLUS-90086 (Tony Hawk's Pro Skater 2 (USA) (Demo))
        gs->AddTrait(GameSettings::Trait::ForceRecompilerLUTFastmem);
        return gs;
    }

    return {};
}

bool isAnalogOnlyGame(const std::string& game_code) {
    static const std::unordered_set<std::string> codes({
        "SCES-01564",
        "SCES-02028",
        "SCES-02029",
        "SCES-02030",
        "SCUS-94423",
        "SCES-02031",
        "SCPS-45411",
        "SCPS-10091",
        "SCPS-91196",
        "SCPS-91331",
    });

    return codes.find(game_code) != codes.end();
}

bool isAnalogPreferedGame (const std::string& game_code) {
    static const std::unordered_set<std::string> codes({
        // Breakout (USA)
        "SLUS-01170",
        // Ridge racer
        "SLUS-00797",
        "SLUS-90049",
        "SCES-01706",
        "SCED-01832",
        "SCPS-45354",
        "SCPS-45355",
        "SCPS-45356",
        "SCPS-45357",
        "SLPS-01800",
        "SLPS-01801",
        // Pong
        "SLUS-00889",
        "SLUS-80889",
        // medal of honor
        "SLES-02470",
        "SLES-02471",
        "SLES-02472",
        "SLUS-00974",
        "SLES-03125",
        "SLES-03124",
        "SLES-03126",
        "SLUS-01270",
        "SLUS-90072",
        // big list found on internet
        "SLUS-00709",
        "SCES-02028",
        "SCES-02029",
        "SCES-02030",
        "SCUS-94423",
        "SCES-02031",
        "SLPS-01512",
        "SLPS-01510",
        "SLPS-01511",
        "SLES-03552",
        "SLUS-01324",
        "SLPS-02728",
        "SLPM-87395",
        "SLUS-01041",
        "SLPM-87396",
        "SLUS-01080",
        "SCPS-10047",
        "SCES-00967",
        "SCES-00967",
        "SCUS-94154",
        "SCPS-10073",
        "PAPX-90070",
        "SCES-01420",
        "SCPS-10140",
        "SCPS-10118",
        "SCUS-94244",
        "SCES-02834",
        "SCUS-94570",
        "SCUS-94654",
        "SLPM-86222",
        "SLUS-01280",
        "SLPM-86252",
        "SLPM-86370",
        "SLPM-86503",
        "SLUS-01446",
        "SLPM-86693",
        "SLUS-01281",
        "SLES-03221",
        "SLES-03222",
        "SLES-03223",
        "SLPM-80573",
        "SLPM-86627",
        "SLES-03225",
        "SLUS-01279",
        "SCED-02062",
        "SLED-02259",
        "SCES-02080",
        "SLES-02081",
        "SLES-02082",
        "SLES-02083",
        "SLPM-87384",
        "SLES-02084",
        "SLUS-00892",
        "SCES-12080",
        "SLES-12081",
        "SLES-12082",
        "SLES-12083",
        "SLPM-87385",
        "SLES-12084",
        "SLUS-00908",
        "SCES-22080",
        "SLES-22081",
        "SLES-22082",
        "SLES-22083",
        "SLPM-87386",
        "SLES-22084",
        "SLUS-00909",
        "SCES-32080",
        "SLES-32081",
        "SLES-32082",
        "SLES-32083",
        "SLPM-87387",
        "SLES-32084",
        "SLUS-00910",
        "SLES-02965",
        "SLES-02966",
        "SLES-02967",
        "SLES-02968",
        "SLPS-02000",
        "SLES-02969",
        "SLUS-01251",
        "SLUS-01251",
        "SLES-12965",
        "SLES-12966",
        "SLES-12967",
        "SLES-12968",
        "SLPS-02001",
        "SLES-12969",
        "SLUS-01295",
        "SLUS-01295",
        "SLES-22965",
        "SLES-22966",
        "SLES-22967",
        "SLES-22968",
        "SLPS-02002",
        "SLES-22969",
        "SLUS-01296",
        "SLUS-01296",
        "SLES-32965",
        "SLES-32966",
        "SLES-32967",
        "SLES-32968",
        "SLPS-02003",
        "SLES-32969",
        "SLUS-01297",
        "SLUS-01297",
        "SCPS-10045",
        "PAPX-90026",
        "SCES-00984",
        "SCES-00984",
        "SCUS-94257",
        "SCUS-94194",
        "SCUS-94194",
        "SCUS-94455",
        "SCUS-94455",
        "SCES-02380",
        "SCPS-10116",
        "SCES-12380",
        "SCPS-10117",
        "SCPS-10117",
        "SCUS-94488",
        "SCUS-94488",
        "SCUS-94488",
        "SCUS-94588",
        "SLES-02781",
        "SLES-02781",
        "SLUS-01115",
        "SCUS-94555",
        "SLES-01370",
        "SLES-01506",
        "SLES-01507",
        "SLES-01508",
        "SLPM-86111",
        "SLES-01734",
        "SLUS-00594",
        "SLUS-00594",
        "SLES-11370",
        "SLES-11506",
        "SLES-11507",
        "SLES-11508",
        "SLPM-86112",
        "SLES-11734",
        "SLUS-00776",
        "SLUS-00776",
        "PAPX-90044",
        "SCPS-45412",
        "SCPS-45413",
        "SCPS-45414",
        "SLES-02136",
        "SLUS-00957",
        "SLUS-90062",
        "SLES-00658",
        "SLUS-00276",
        "SLES-01154",
        "SLUS-00620",
        "SLES-01876",
        "SLUS-00826",
        "SLES-02689",
        "SLES-02700",
        "SLUS-01104",
        "SLES-01788",
        "SLES-01789",
        "SLUS-01003",
        "SLPS-00895",
        "SLPS-01593",
        "SLPS-02099",
        "SLPS-01230",
        "SLUS-00662",
        "SLPS-01231",
        "SLUS-00668",
        "SLES-02558",
        "SLES-02559",
        "SLES-02560",
        "SLES-02562",
        "SLPS-02480",
        "SLES-02561",
        "SLUS-01042",
        "SLES-12558",
        "SLES-12559",
        "SLES-12560",
        "SLES-12562",
        "SLPS-02481",
        "SLES-12561",
        "SLUS-01055",
        "SLES-01760",
        "SLPS-02085",
        "SLUS-00277",
        "SCES-00409",
        "SIPS-60016",
        "SCUS-94187",
        "SLUS-00748",
        "SLUS-00756",
        "SLES-02529",
        "SLED-02541",
        "SLES-02530",
        "SLES-02531",
        "SLES-02698",
        "SLES-02533",
        "SLES-02532",
        "SLUS-00923",
        "SLUS-90064",
        "SLUS-00747",
        "SLES-03753",
        "SLUS-01397",
        "SCES-02104",
        "SCUS-94425",
        "SCES-01438",
        "SCPS-10083",
        "SCUS-94228",
        "SCUS-94290",
        "SCES-02835",
        "SCES-02835",
        "SCUS-94467",
        "SCUS-94467",
        "SLUS-90029",
        "SCES-02159",
        "SCES-02161",
        "SLPM-86105",
        "SLPM-87357",
        "SCUS-94421",
        "SCES-12159",
        "SCES-12161",
        "SLPM-86106",
        "SLPM-87358",
        "SCUS-94422",
        "SCES-01753",
        "SCPS-18011",
        "SCUS-94448",
        "SCUS-94398",
        "SLES-01907",
        "SLPS-02516",
        "SLES-02754",
        "SLES-02755",
        "SLES-02756",
        "SLPM-87393",
        "SLUS-01040",
        "SLUS-90063",
        "SCES-02845",
    });

    return codes.find(game_code) != codes.end();
}
