#pragma once

#include <QWidget>
#include <QFrame>

#include "../../Tools/SvgToPixmap.hpp"
#include "../Page.h"

class LocalFolderPage : public Page {
private:

public:
  LocalFolderPage(QWidget* parent = nullptr);
  ~LocalFolderPage( );

  std::string GetName( ) { return "localFolder"; }
};
