#pragma once

#include <QWidget>
#include <QFrame>

#include "../../Tools/SvgToPixmap.hpp"
#include "../Page.h"

class HomePage : public Page {
  Q_OBJECT
private:

public:
  HomePage(QWidget* parent = nullptr);
  ~HomePage( );

  std::string GetName( ) { return "home"; }
};
