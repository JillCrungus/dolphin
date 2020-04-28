#include "Core/TS/TSConfigManager.h"
#include "Common/Config/Config.h"
#include "Common/FileUtil.h"
#include "Common/IniFile.h"
#include "Common/Logging/Log.h"

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
}

void TSConfig::LoadDefaults()
{
  bSkipVideos = false;
  bVerticalSplitscreen = false;
}
