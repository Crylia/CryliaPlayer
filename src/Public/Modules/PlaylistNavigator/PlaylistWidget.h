#pragma once

#include <QWidget>
#include <QFrame>
#include <QLayout>

class PlaylistWidget : public QFrame {

  Q_OBJECT

private:

public:
  PlaylistWidget(QWidget* parent);
  ~PlaylistWidget( );
};
