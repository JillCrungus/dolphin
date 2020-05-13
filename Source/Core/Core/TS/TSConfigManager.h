#pragma once

#include <string>
#include "Common/Common.h"
#include "Common/CommonTypes.h"
#include "UICommon/DiscordPresence.h"

class IniFile;

struct TSConfig
{
  bool bSkipVideos = false;
  bool bVerticalSplitscreen = false;
  bool bFixButtonCodes = true;

  void LoadDefaults();

  TSConfig(const TSConfig&) = delete;
  TSConfig& operator=(const TSConfig&) = delete;
  TSConfig(TSConfig&&) = delete;
  TSConfig& operator=(TSConfig&&) = delete;

  // Save settings
  void SaveSettings();

  // Load settings
  void LoadSettings();

  // Util
  void SetLevel( u32 newlevel )
  {
    m_current_level = newlevel;
    Discord::UpdateDiscordPresence();
  }
  u32 GetLevelID();
  std::string GetDefaultLevelNameForID(u32 id);

  // Return the permanent and somewhat globally used instance of this struct
  static TSConfig& GetInstance() { return (*m_Instance); }
  static void Init();
  static void Shutdown();

private:
  TSConfig();
  ~TSConfig();

  void SaveGeneralSettings(IniFile& ini);
  void LoadGeneralSettings(IniFile& ini);

  static TSConfig* m_Instance;

  u32 m_current_level;
};
