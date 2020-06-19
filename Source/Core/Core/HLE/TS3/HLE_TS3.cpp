#include "Core/HLE/TS3/HLE_TS3.h"

#include <bitset>
#include "Common/Common.h"
#include "Common/CommonTypes.h"
#include "Common/Logging/Log.h"
#include "Core/GeckoCode.h"
#include "Core/HW/CPU.h"
#include "Core/Host.h"
#include "Core/PowerPC/MMU.h"
#include "Core/PowerPC/PowerPC.h"
#include "Core/TS/TSConfigManager.h"
#include "UICommon//DiscordPresence.h"

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

void TestDisplayText()
{
  rPS(1).SetPS0(20.0);
  rPS(2).SetPS0(60.0);
  GPR(3) = 0x8044ecb0;
  GPR(4) = 2139062143;
  GPR(5) = 127;

  LR = PC + 4;
  NPC = 0x8000bde0;
}

void HLE_UpdateCurrentLevel()
{
  TSConfig::GetInstance().SetLevel(PowerPC::HostRead_U32(0x80612614));
}

void HLE_DebugButtonCheat()
{
  int param_1 = GPR(3);
  int current = GPR(4);
  std::bitset<8> bitsnb(param_1);
  std::bitset<8> bitsc(current);

  INFO_LOG(TS3, "[Button cheat] param_1: %Xh current: %Xh", param_1, current);

  // TestDisplayText();
  /*
  rPS(1).SetPS0(20.0);
  rPS(2).SetPS0(60.0);
  GPR(3) = 0x8044ecb0;
  GPR(4) = 2139062143;
  GPR(5) = 127;

  LR = PC + 4;
  NPC = 0x8000bde0;
  */
}
void HLE_ButtonCheatInputCheck()
{
  u16 param_1 = (u16)GPR(3);
  u16 currentbutton = (u16)GPR(4);

  if ((param_1 & 255U) == 0)
  {
    NPC = LR;
    return;
  }

  // INFO_LOG(TS3, "[Button cheat] param_1: %Xh current: %Xh", param_1, currentbutton);

  int currentbufferpos = PowerPC::HostRead_U32(BUTTON_BUFFER_POS_ADDR);
  int currentbufferaddress = BUTTON_BUFFER_ADDR + (currentbufferpos * 2);

  int lastbufferpos = (currentbufferpos - 1) % 20;
  int lastbufferaddress = BUTTON_BUFFER_ADDR + (lastbufferpos * 2);

  u16 lastButton = PowerPC::HostRead_U16(lastbufferaddress);

  // FRD didn't do this check, making button codes frame perfect...
  if (lastButton == currentbutton)
  {
    NPC = LR;
    return;
  }

  PowerPC::HostWrite_U16(currentbutton % 3839, currentbufferaddress);
  PowerPC::HostWrite_U32((currentbufferpos + 1) % 20, BUTTON_BUFFER_POS_ADDR);
  NPC = LR;
}

void HLE_DebugUnlockAll()
{
  u32 val = PowerPC::HostRead_U32(0x806125f4);

  u32 testVal = 1 - val;

  INFO_LOG(TS3, "[Button cheat] Unlock all! Starting value: %i, guessed value after call: %i", val,
           testVal);
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
