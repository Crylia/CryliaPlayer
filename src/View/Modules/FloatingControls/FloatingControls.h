#pragma once

#include "../../../Controller/MusicPlayer/MusicPlayer.h"
#include "../../Tools/SvgToPixmap.hpp"

#include <QFrame>
#include <QSlider>
#include <QPushButton>
#include <QObject>
#include <filesystem>
#include <QStackedLayout>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsBlurEffect>
#include <QLayout>
#include <QWidget>
#include <QLabel>
#include <string>
#include <QPixmap>
#include <QtSvg>
#include <QSvgRenderer>
#include <QPainter>
#include <QMainWindow>
#include <QApplication>

enum Repeat : short;

class FloatingControls : public QFrame {

  Q_OBJECT

public:

  FloatingControls(QWidget* parent = nullptr);
  ~FloatingControls( );

private:
  MusicPlayer& musicPlayer = MusicPlayer::getInstance( );

  QLabel* m_artist;
  QLabel* m_title;
  QLabel* m_album;
  QLabel* m_albumArt;

  QLabel* m_volume;
  QLabel* m_volumeIcon;

  QLabel* m_songPos;
  QLabel* m_songDur;

  QPushButton* m_playPause;
  QPushButton* m_shuffle;
  QPushButton* m_loop;
  QPushButton* m_skipNext;
  QPushButton* m_skipPrev;

  QPushButton* m_fullscreen;

  QSlider* m_songProgress;
  QSlider* m_volumeSlider;

  bool fullscreen;

signals:
  void SongChanged( );

private slots:
  void setShuffle(bool shuffle);
  void setLoop(Loop loop);
  void volumeChanged( );
  void playPause( );

  void setTitle( );
};
