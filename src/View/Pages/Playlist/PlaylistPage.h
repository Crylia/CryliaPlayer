#pragma once

#include <QWidget>
#include <QFrame>
#include "../../Tools/SvgToPixmap.hpp"

class PlaylistPage : public QFrame {
  Q_OBJECT
private:
public:
  PlaylistPage(QWidget* parent = nullptr);
  ~PlaylistPage( );
};
