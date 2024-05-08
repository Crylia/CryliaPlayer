#pragma once

#include "../../../Controller/MusicPlayer/MusicPlayer.hpp"
#include "../../Tools/SvgToPixmap.hpp"

#include <QApplication>
#include <QFrame>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QSlider>
#include <QStackedLayout>
#include <QSvgRenderer>
#include <QWidget>
#include <QtSvg>

enum Repeat : short;

class FloatingControls : public QFrame {

  Q_OBJECT

public:
  FloatingControls(QWidget *parent = nullptr);
  ~FloatingControls();

private:
  MusicPlayer &musicPlayer = MusicPlayer::getInstance();

  QLabel *m_artist;
  QLabel *m_title;
  QLabel *m_album;
  QLabel *m_albumArt;

  QLabel *m_volume;
  QLabel *m_volumeIcon;

  QLabel *m_songPos;
  QLabel *m_songDur;

  QPushButton *m_playPause;
  QPushButton *m_shuffle;
  QPushButton *m_loop;
  QPushButton *m_skipNext;
  QPushButton *m_skipPrev;

  QPushButton *m_fullscreen;

  QSlider *m_songProgress;
  QSlider *m_volumeSlider;

  // Timer to update the song's duration and slider
  QTimer *m_progressUpdateTimer;

  bool fullscreen;

signals:
  void SongChanged();

private slots:
  void setShuffle(bool shuffle);
  void setLoop(Loop loop);
  void volumeChanged();
  void playPause();

  void setTitle();
  void setSongDur();
};
