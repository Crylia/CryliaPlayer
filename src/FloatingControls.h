#pragma once

#include "datetime.h"

#include <QFrame>
#include <QSlider>
#include <QPushButton>

enum Repeat : short;

class FloatingControls : public QFrame {

  Q_OBJECT

private:
  tools::DateTime timestamp;
  tools::DateTime songDuration;
  std::string albumArtPath;
  int volume;
  bool fullscreen;
  bool shuffle;
  bool playPause;
  Repeat songRepeat;

public:
  QPixmap AlbumArt;
  std::string Artist;
  std::string SongName;

  QPushButton SongRepeatImg;
  QPushButton PrevSongImg;
  QPushButton NextSongImg;
  QPushButton PlayImg;
  QPushButton PauseImg;
  QPushButton ShuffleImg;
  QSlider DurationSlider;

  QSlider VolumeSlider;
  QPushButton FullscreenToggle;

  FloatingControls(QWidget* parent = nullptr);
  ~FloatingControls( );
};
