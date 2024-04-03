#pragma once

#include <QWidget>
#include <QFrame>

#include "../../Tools/SvgToPixmap.hpp"
#include "../Page.h"

class SettingsPage : public Page {
  Q_OBJECT
private:

public:
  SettingsPage(QWidget* parent = nullptr);
  ~SettingsPage( );

  std::string GetName( ) { return "settings"; }
};
