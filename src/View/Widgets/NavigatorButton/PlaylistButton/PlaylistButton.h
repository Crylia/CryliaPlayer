#pragma once

#include "../NavButton.h"

class PlaylistButton : public NavButton {
private:
  //!Add Associated Playlist
public:
  PlaylistButton(QString, QString, QString, Page*, QWidget*);
  PlaylistButton(QString, QString, QPixmap, Page*, QWidget*);
  ~PlaylistButton( );

  void Select( );
  void Unselect( );
};

