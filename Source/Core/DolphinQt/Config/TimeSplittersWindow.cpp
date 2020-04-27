#include <QDialogButtonBox>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGroupBox>

#include "DolphinQt/Config/TimeSplittersWindow.h"
#include "DolphinQt/QtUtils/WrapInScrollArea.h"
#include "DolphinQt/Resources.h"
#include "DolphinQt/Settings.h"

#include "Core/Core.h"
#include "Common/Config/Config.h"
#include "Core/TS/TSConfigManager.h"

TSConfigWindow::TSConfigWindow(QWidget* parent) : QDialog(parent)
{
  // Set Window Properties
  setWindowTitle(tr("TSFP Settings"));
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  // Main Layout
  QVBoxLayout* layout = new QVBoxLayout;

  // Add content to layout before dialog buttons.
  m_tab_widget = new QTabWidget();
  layout->addWidget(m_tab_widget);

  m_tab_widget->addTab(GetWrappedWidget(new TSGeneralPane, this, 125, 100), tr("General"));

  // Dialog box buttons
  QDialogButtonBox* close_box = new QDialogButtonBox(QDialogButtonBox::Close);

  connect(close_box, &QDialogButtonBox::rejected, this, &QDialog::reject);

  layout->addWidget(close_box);

  setLayout(layout);
}

void TSConfigWindow::SelectGeneralPane()
{
  m_tab_widget->setCurrentIndex(static_cast<int>(TSTabIndex::General));
}

TSGeneralPane::TSGeneralPane(QWidget* parent) : QWidget(parent)
{
  CreateLayout();
  LoadConfig();

  ConnectLayout();

  connect(&Settings::Instance(), &Settings::EmulationStateChanged, this,
          &TSGeneralPane::OnEmulationStateChanged);

  OnEmulationStateChanged(Core::GetState());
}

void TSGeneralPane::CreateLayout()
{
  m_main_layout = new QVBoxLayout;
  // Create layout here
  CreateBasic();

  m_main_layout->addStretch(1);
  setLayout(m_main_layout);
}

void TSGeneralPane::OnEmulationStateChanged(Core::State state)
{
  const bool running = state != Core::State::Uninitialized;

  m_checkbox_skipvideos->setEnabled(!running);
}

void TSGeneralPane::ConnectLayout()
{
  connect(m_checkbox_skipvideos, &QCheckBox::toggled, this, &TSGeneralPane::OnSaveConfig);
}

void TSGeneralPane::CreateBasic()
{
  auto* basic_group = new QGroupBox(tr("Basic Settings"));
  auto* basic_group_layout = new QVBoxLayout;
  basic_group->setLayout(basic_group_layout);
  m_main_layout->addWidget(basic_group);

  m_checkbox_skipvideos = new QCheckBox(tr("Skip videos (EA + FRD logos, attract screen)"));
  basic_group_layout->addWidget(m_checkbox_skipvideos);
}

void TSGeneralPane::LoadConfig()
{
  m_checkbox_skipvideos->setChecked(TSConfig::GetInstance().bSkipVideos);
}

void TSGeneralPane::OnSaveConfig()
{
  Config::ConfigChangeCallbackGuard config_guard;

  auto& settings = TSConfig::GetInstance();

  settings.bSkipVideos = m_checkbox_skipvideos->isChecked();
  //Config::SetBaseOrCurrent(Config::MAIN_CPU_THREAD, m_checkbox_dualcore->isChecked());

  settings.SaveSettings();
}
