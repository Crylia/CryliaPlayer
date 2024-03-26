#pragma once

#include "../../../core/audio/audio.h"
#include "../../Tools/SvgToPixmap.hpp"

#include <QFrame>
#include <QSlider>
#include <QPushButton>
#include <QObject>
#include <filesystem>
#include <QStackedLayout>

enum Repeat : short;

class FloatingControls : public QFrame {

  Q_OBJECT

    Q_PROPERTY(QString artist READ getArtist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString songName READ getSongName WRITE setSongName NOTIFY songNameChanged)
    Q_PROPERTY(int songPos READ getSongPos WRITE setSongPos NOTIFY songPosChanged)
public:

  QString getArtist( ) const {
    return artist;
  }
  void setArtist(QString artist) {
    if (this->artist == artist)
      return;

    this->artist = artist;
    emit artistChanged(artist);
  }

  QString getSongName( ) const {
    return songName;
  }
  void setSongName(QString songName) {
    if (this->songName == songName)
      return;

    this->songName = songName;
    emit songNameChanged(songName);
  }

  int getSongPos( ) const {
    return songPos;
  }
  void setSongPos(int pos) {
    if (this->songPos == pos)
      return;
    this->songPos = pos;
    emit songPosChanged(pos);
  }

  void togglePlayPause( ) {
    this->playPause = !this->playPause;
  }

  bool GetPlayPause( ) {
    return this->playPause;
  }

  FloatingControls(QWidget* parent = nullptr, std::filesystem::path path = std::filesystem::path( ));
  ~FloatingControls( );

signals:
  void artistChanged(QString artist);
  void songNameChanged(QString songName);
  void songPosChanged(int songPos);

private:
  QString artist;
  QString songName;

  QString albumArtPath;
  int volume;
  bool fullscreen;
  bool shuffle;
  bool playPause;
  Repeat songRepeat;
  QPixmap albumArt;
  int songPos;
  int songLength;

  Audio& song;
};
