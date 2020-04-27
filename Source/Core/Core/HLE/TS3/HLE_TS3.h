#pragma once

// TSFP HLE Hooks

namespace HLE_TS3
{
typedef struct challengecharacterset_s
{
  int char_type;
  float health_mult;
  int team;
  int unk1;
} challengecharacterset;

// Interesting constants
constexpr u32 PAD_FILE_TEMPLATE_ADDRESS = 0x803fee88;
constexpr u32 CURRENT_LEVEL_NUMBER_ADDRESS = 0x80612614;

constexpr u32 LOAD_BINDPOSE_ADDRESS = 0x800265b8;
void HLE_LoadBindPose();

constexpr u32 GET_PAD_PATH_ADDRESS = 0x8006bc30;
void HLE_GetCurrentLevelPADPath();

constexpr u32 SET_NEXT_MUSIC_TRACK_ADDRESS = 0X801a16ec;
constexpr u32 g_MusicToPlay = 0x805be598;
void SetNextMusicTrack();

constexpr u32 CHALLENGE_LAST_STAND_HORROR_CHRSET_PTR_LOC = 0x8045f6ec;

constexpr u32 PLAY_THP_ADDRESS = 0x801821bc;

static challengecharacterset test_set[] = {
  {25, 1.0f, 0},
  {37, 1.0f, 0},
  {-1}
};

}  // namespace HLE_TS3
