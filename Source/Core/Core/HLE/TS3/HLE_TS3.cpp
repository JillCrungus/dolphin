#include "Core/HLE/HLE_Misc.h"

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

}  // namespace HLE_TS3
