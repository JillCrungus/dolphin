#include "Core/HLE/TS3/HLE_TS3.h"

#include "Common/Common.h"
#include "Common/CommonTypes.h"
#include "Common/Logging/Log.h"
#include "Core/GeckoCode.h"
#include "Core/HW/CPU.h"
#include "Core/Host.h"
#include "Core/PowerPC/MMU.h"
#include "Core/PowerPC/PowerPC.h"

namespace HLE_TS3
{
void HLE_LoadBindPose()
{
  // INFO_LOG(TS3, "Bind pose loading function called!");

  u32 param_1 = GPR(3);
  u32 param_2 = GPR(4);

  const char* filename = PowerPC::HostGetString(GPR(5)).c_str();

  u32 param_4 = GPR(6);

  u32 param_5 = GPR(7);

  INFO_LOG(TS3,
           "LoadBindPose(): param_1 = %i\nLoadBindPose(): param_2 = %i\nLoadBindPose(): filename = "
           "%s\nLoadBindPose(): param_4 = %i\n",
           param_1, param_2, filename, param_4, param_5);

  // Following section is reconstructed from Ghidra C pseudocode;
  int iVar1 = param_1 * 0xc;
  INFO_LOG(TS3, "LoadBindPose(): iVar1 = %i", iVar1);

  if (param_5 == 0)
  {
    INFO_LOG(TS3, "LoadBindPose(): Writing param_2 (%i) to the mystery location!", param_2);
  }

  INFO_LOG(TS3, "Calling FUN_80022438(%s, %i, 0)", filename, param_2);
}

void HLE_GetCurrentLevelPADPath()
{
  u32 currLevelID = PowerPC::HostRead_U32(CURRENT_LEVEL_NUMBER_ADDRESS);
  std::string padTemplate = PowerPC::HostGetString(PAD_FILE_TEMPLATE_ADDRESS);

  INFO_LOG(TS3, "Current level: %i", currLevelID);

  char finalPath[64];
  memset(finalPath, 0, sizeof(finalPath));

  sprintf(finalPath, padTemplate.c_str(), currLevelID);

  INFO_LOG(TS3, "PAD path for current level: %s", finalPath);
}

void HLE_DebugWindowSet()
{
  u32 x1 = GPR(4);
  u32 y1 = GPR(5);

  u32 x2 = GPR(6);
  u32 y2 = GPR(7);

  INFO_LOG(TS3, "[Setting window] x1: %i, y1: %i, x2: %i, y2: %i ", x1, y1, x2, y2);
}

void SetNextMusicTrack()
{
  /*
  std::string filename = PowerPC::HostGetString(GPR(3));
  u32 param_2 = PowerPC::HostRead_U32(GPR(4));
  u32 param_3 = PowerPC::HostRead_U32(GPR(5));

  INFO_LOG(TS3, "Setting next track to %s with parameters %i %i", filename.c_str(), param_2,
           param_3);

  //PowerPC::HostWrite_String(filename.c_str(), g_MusicToPlay);

  //PowerPC::HostWrite_U32(1, 0x805ad4b8);
  //PowerPC::HostWrite_U32(param_2, 0x805ad4bc);
  //PowerPC::HostWrite_U32(param_3, 0x805ad4c0);

  GPR(3) = 0;
  */
}

}  // namespace HLE_TS3
