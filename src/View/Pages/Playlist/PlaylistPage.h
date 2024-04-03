#pragma once

#include <QWidget>
#include <QFrame>

#include "../../Tools/SvgToPixmap.hpp"
#include "../Page.h"

class PlaylistPage : public Page {
  Q_OBJECT
private:

public:
  PlaylistPage(QWidget* parent = nullptr);
  ~PlaylistPage( );

  std::string GetName( ) { return "playlist"; }
};
