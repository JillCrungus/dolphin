#pragma once

// TSFP HLE Hooks

namespace HLE_TS3
{
//Interesting constants
constexpr u32 PAD_FILE_TEMPLATE_ADDRESS = 0x803fee88;
constexpr u32 CURRENT_LEVEL_NUMBER_ADDRESS = 0x80612614;

constexpr u32 LOAD_BINDPOSE_ADDRESS = 0x800265b8;
void HLE_LoadBindPose();

constexpr u32 GET_PAD_PATH_ADDRESS = 0x8006bc30;
void HLE_GetCurrentLevelPADPath();


constexpr u32 SET_NEXT_MUSIC_TRACK_ADDRESS = 0X801a16ec;
constexpr u32 g_MusicToPlay = 0x805be598;
void SetNextMusicTrack();

}  // namespace HLE_TS3
