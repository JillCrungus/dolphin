#pragma once

#include <QDialog>

class QTabWidget;
class QCheckBox;
class QComboBox;
class QLabel;
class QPushButton;
class QRadioButton;
class QSlider;
class QVBoxLayout;

namespace Core
{
enum class State;
}

enum class TSTabIndex
{
  General = 0
};

class TSConfigWindow final : public QDialog
{
  Q_OBJECT
public:
  explicit TSConfigWindow(QWidget* parent = nullptr);
  void SelectGeneralPane();

private:
  QTabWidget* m_tab_widget;
};

class TSGeneralPane final : public QWidget
{
  Q_OBJECT
public:
  explicit TSGeneralPane(QWidget* parent = nullptr);

private:
  void CreateLayout();
  void ConnectLayout();
  void CreateBasic();

  void LoadConfig();
  void OnSaveConfig();
  void OnEmulationStateChanged(Core::State state);

  // Widgets
  QVBoxLayout* m_main_layout;
  QCheckBox* m_checkbox_skipvideos;
  QCheckBox* m_checkbox_verticalsplit;
};
