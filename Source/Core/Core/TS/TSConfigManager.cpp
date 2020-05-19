#include "Core/TS/TSConfigManager.h"
#include "Common/Config/Config.h"
#include "Common/FileUtil.h"
#include "Common/IniFile.h"
#include "Common/Logging/Log.h"
#include "Core/Core.h"
#include "Core/PowerPC/MMU.h"

TSConfig* TSConfig::m_Instance;

TSConfig::TSConfig()
{
  LoadDefaults();
  // Make sure we have log manager
  LoadSettings();
}

void TSConfig::Init()
{
  m_Instance = new TSConfig;
}

void TSConfig::Shutdown()
{
  delete m_Instance;
  m_Instance = nullptr;
}

TSConfig::~TSConfig()
{
  SaveSettings();
}

void TSConfig::SaveSettings()
{
  NOTICE_LOG(BOOT, "Saving TS settings to %s", File::GetUserPath(F_TSCONFIG_IDX).c_str());
  IniFile ini;
  ini.Load(File::GetUserPath(F_TSCONFIG_IDX));  // load first to not kill unknown stuff

  SaveGeneralSettings(ini);

  ini.Save(File::GetUserPath(F_TSCONFIG_IDX));

  Config::Save();
}

void TSConfig::SaveGeneralSettings(IniFile& ini)
{
  IniFile::Section* general = ini.GetOrCreateSection("General");

  // General
  general->Set("SkipVideos", bSkipVideos);
  general->Set("VerticalSplit", bVerticalSplitscreen);
  general->Set("FixButtonCodes", bFixButtonCodes);
}

void TSConfig::LoadSettings()
{
  Config::Load();

  INFO_LOG(BOOT, "Loading TS Settings from %s", File::GetUserPath(F_TSCONFIG_IDX).c_str());
  IniFile ini;
  ini.Load(File::GetUserPath(F_TSCONFIG_IDX));

  LoadGeneralSettings(ini);
}

void TSConfig::LoadGeneralSettings(IniFile& ini)
{
  IniFile::Section* general = ini.GetOrCreateSection("General");

  general->Get("SkipVideos", &bSkipVideos, false);
  general->Get("VerticalSplit", &bVerticalSplitscreen, false);
  general->Get("FixButtonCodes", &bFixButtonCodes, true);
}

void TSConfig::LoadDefaults()
{
  bSkipVideos = false;
  bVerticalSplitscreen = false;
  bFixButtonCodes = true;
}

u32 TSConfig::GetLevelID()
{
  if (Core::IsRunning())
  {
    return m_current_level;
  }
  else
  {
    return -1;
  }
}

std::string TSConfig::GetDefaultLevelNameForID(u32 id)
{
  switch (id)
  {
  case -1:
    return "Not playing";
  case 1:   // 1 - mansion2
    return "Mansion of Madness";
  case 2:   // 2 - intro
    return "Time to Split";
  case 4:   // 4 - castle
    return "Scotland the Brave";
  case 5:   // 5 - farfuture1
    return "The Machine Wars";
  case 6:   // 6 - nearfuture1
    return "Breaking and Entering";
  case 9:   // 9 - nemo
    return "You Take the High Road";
  case 11:  // 11 - train
    return "The Khallos Express";
  case 14:  // 14 - farfuture2
    return "Something to Crow About";
  case 17:  // 17 - catacombs
    return "What Lies Below";
  case 18:  // 18 - depot
    return "The Russian Connection";
  case 22:  // 22 - nearfuture2
    return "U-Genius, U-Genix";
  case 26:  // 26 - outro
    return "Future Perfect";
  case 81:  // 81 - nemoend
    return "The Hooded Man";
  default:
    char fallback[32];
    sprintf(fallback, "Level %i", id);
    return fallback;
  }
}
