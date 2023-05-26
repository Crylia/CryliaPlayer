#pragma once

#include <QFrame>
#include <QSlider>
#include <QPushButton>
#include <QObject>

enum Repeat : short;

class FloatingControls : public QFrame {

  Q_OBJECT

    Q_PROPERTY(QString artist READ getArtist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString songName READ getSongName WRITE setSongName NOTIFY songNameChanged)
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

  FloatingControls(QWidget* parent = nullptr);
  ~FloatingControls( );

signals:
  void artistChanged(QString artist);
  void songNameChanged(QString songName);

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
};
