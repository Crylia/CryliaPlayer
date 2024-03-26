#include <iostream>

#include "FloatingControls.h"
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

enum Repeat : short {
  ALL,
  CURRENT,
  NONE
};

static QPushButton* makeSongControlButton(QString name, QSize size = QSize(36, 36), QString color = "#D7D7D7") {
  QPushButton* button = new QPushButton( );
  button->setObjectName(name);
  button->setStyleSheet(R"(
    QPushButton#)" + name + R"({
      background-color: transparent;
      border: 0;
    }
  )");
  button->setIcon(RenderSvg(":/icons/" + name + ".svg", 36, 36));
  button->setIconSize(size);
  button->setCursor(Qt::PointingHandCursor);
  QGraphicsColorizeEffect* colorize = new QGraphicsColorizeEffect( );
  colorize->setColor(QColor(color));
  colorize->setStrength(1);
  button->setGraphicsEffect(colorize);

  return button;
}

FloatingControls::FloatingControls(QWidget* parent, std::filesystem::path path) :
  QFrame(parent),
  volume(100),
  albumArtPath("default.png"),
  fullscreen(false), shuffle(false),
  playPause(false),
  songRepeat(NONE),
  artist("Artist"),
  songName("Song"),
  song(Audio::getInstance( )) {
  this->setFixedHeight(100);
  this->setObjectName("main");
  this->setStyleSheet(R"(
    QFrame#main{
      background-color:rgba(40, 40 ,40, 0.3);
      border: 4px solid #414141;
      border-radius: 12px;
      margin: 0px 10px 10px 10px;
    }
  )");
  applyShadow(this);

  /* Main Layout to store the Left Center and right controls */
  QHBoxLayout* mainLayout = new QHBoxLayout(this);
  /* Left side Icon, Artist and Song info */
  QHBoxLayout* leftLayout = new QHBoxLayout( );
  leftLayout->setSpacing(10);
  leftLayout->setAlignment(Qt::AlignLeft);

  // Album Art
  QLabel* albumArt = new QLabel( );
  albumArt->setObjectName("albumArt");
  albumArt->setAlignment(Qt::AlignCenter);
  albumArt->setStyleSheet(R"(
    QLabel#albumArt{
      border: 4px solid #414141;
      border-radius: 8px;
    }
  )");
  //! Change later to the actual album art when the controls are done
  albumArt->setPixmap(song.GetAlbumCover( ).scaled(QSize(64, 64), Qt::IgnoreAspectRatio));
  leftLayout->addWidget(albumArt);

  // Artist and Song name layout
  QVBoxLayout* artistSongLayout = new QVBoxLayout( );
  QLabel* artist = new QLabel(QString::fromStdString(song.GetArtist( )));
  artist->setMinimumWidth(50);
  connect(this, &FloatingControls::artistChanged, artist, &QLabel::setText);
  artist->setObjectName("artist");
  artist->setStyleSheet(R"(
    QLabel#artist{
      font-size: 16px;
      font-weight: bold;
      color: #E1E1E1;
    }
  )");

  QLabel* songName = new QLabel( );
  songName->setMinimumWidth(50);
  QFontMetrics metrics(songName->font( ));
  songName->setText(metrics.elidedText(QString::fromStdString(song.GetTitle( )), Qt::ElideRight, songName->width( )));

  connect(this, &FloatingControls::songNameChanged, songName, &QLabel::setText);
  songName->setObjectName("title");
  songName->setStyleSheet(R"(
    QLabel#songName{
      font-size: 14px;
      color: #D7D7D7;
    }
  )");
  artistSongLayout->addWidget(artist);
  artistSongLayout->addWidget(songName);
  leftLayout->addLayout(artistSongLayout);

  /* Center layout to store the song controls and pos bar */
  QVBoxLayout* centerLayout = new QVBoxLayout( );
  centerLayout->setAlignment(Qt::AlignCenter);

  mainLayout->setStretchFactor(leftLayout, 1);
  mainLayout->setStretchFactor(centerLayout, 0.1);

  QHBoxLayout* songControlsLayout = new QHBoxLayout( );
  songControlsLayout->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

  QString buttonNames[5] = { "shuffle", "prevSong", "play", "nextSong", "songRepeat" };
  QString col = "#D7D7D7";
  for (int i = 0; i < 5; i++) {
    if (buttonNames[i] == "shuffle" || buttonNames[i] == "songRepeat")
      col = "#CC79AB";
    else
      col = "#D7D7D7";
    QPushButton* pb = makeSongControlButton(buttonNames[i], QSize(36, 36), col);
    if (buttonNames[i] == "play") {
      //TODO Change later
      QObject::connect(pb, &QPushButton::clicked, [pb, this]( ) {
        if (!song.IsMusicPlaying( )) {
          song.StartMusic( );
          pb->setIcon(RenderSvg(":/icons/pause.svg", 36, 36));
          return;
        }
        if (GetPlayPause( )) {
          song.ResumeMusic( );
          pb->setIcon(RenderSvg(":/icons/pause.svg", 36, 36));
        }
        else {
          song.PauseMusic( );
          pb->setIcon(RenderSvg(":/icons/play.svg", 36, 36));
        }
        togglePlayPause( );
        });
    }
    songControlsLayout->addWidget(pb);

  }


  centerLayout->addLayout(songControlsLayout);

  QHBoxLayout* songScrollerLayout = new QHBoxLayout( );
  songScrollerLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

  // Song timestamp
  QLabel* songTimestamp = new QLabel("00:00");
  songTimestamp->setText(
    QTime(
      0,
      song.GetMusicPos( ) / 60,
      song.GetMusicPos( ) % 60
    ).toString("mm:ss"));
  songTimestamp->setObjectName("songTimestamp");
  songTimestamp->setStyleSheet(R"(
    QLabel#songTimestamp{
      font-size: 14px;
      color: #D7D7D7;
    }
  )");
  songTimestamp->setAlignment(Qt::AlignRight);

  // Song duration
  QLabel* songDuration = new QLabel("00:00");
  songDuration->setText(
    QTime(
      0,
      song.GetMusicDuration( ) / 60,
      song.GetMusicDuration( ) % 60
    ).toString("mm:ss"));
  songDuration->setObjectName("songDuration");
  songDuration->setStyleSheet(R"(
    QLabel#songDuration{
      font-size: 14px;
      color: #D7D7D7;
    }
  )");

  // Song duration slider
  QSlider* songDurationSlider = new QSlider(Qt::Horizontal);
  songDurationSlider->setObjectName("songDurationSlider");
  songDurationSlider->setRange(0, song.GetMusicDuration( ));
  songDurationSlider->setValue(song.GetMusicPos( ));
  songDurationSlider->setFixedHeight(28);
  songDurationSlider->setStyleSheet(R"(
    QSlider#songDurationSlider::groove:horizontal{
      border-radius: 4px;
      height: 8px;
      background: #414141;
    }
    QSlider#songDurationSlider::handle:horizontal{
      background: #78AB70;
      border: 4px solid #414141;
      width: 14px;
      height: 14px;
      margin: -7px 0;
      border-radius: 10px;
      padding: -8px 0;
    }
    QSlider#songDurationSlider::sub-page:horizontal{
      background: #78AB70;
      border-radius: 4px;
      height: 8px;
    }
  )");
  songDurationSlider->setCursor(Qt::PointingHandCursor);

  connect(songDurationSlider, &QSlider::sliderReleased, [this, songDurationSlider]( ) {
    song.SetMusicPos(songDurationSlider->value( ));
    });

  songScrollerLayout->addWidget(songTimestamp);
  songScrollerLayout->addWidget(songDurationSlider);
  songScrollerLayout->addWidget(songDuration);

  QTimer* timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this, [this, songTimestamp, songDurationSlider]( ) {
    int sec = song.GetMusicPos( );

    songTimestamp->setText(
      QTime(
        0,
        sec / 60,
        sec % 60
      ).toString("mm:ss"));

    songDurationSlider->setValue(sec);
    //std::cout << songTimestamp->text( ).toStdString( ) << std::endl;
    });
  timer->start(1000);

  centerLayout->addLayout(songScrollerLayout);

  /* Right side layout to store the volume and fullscreen controls */
  QHBoxLayout* rightLayout = new QHBoxLayout( );
  rightLayout->setAlignment(Qt::AlignRight);

  //Volume icon
  QLabel* volumeIcon = new QLabel( );
  volumeIcon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  volumeIcon->setObjectName("volumeIcon");
  volumeIcon->setPixmap(RenderSvg(":icons/volume-high.svg", 36, 36).scaled(QSize(24, 24), Qt::IgnoreAspectRatio));
  QGraphicsColorizeEffect* colorize = new QGraphicsColorizeEffect( );
  colorize->setColor(QColor("#78AB70"));
  colorize->setStrength(1);
  volumeIcon->setGraphicsEffect(colorize);
  rightLayout->addWidget(volumeIcon);

  //Volume slider
  QSlider* VolumeSlider = new QSlider(Qt::Horizontal);
  VolumeSlider->setObjectName("volumeSlider");
  VolumeSlider->setRange(0, 128);
  VolumeSlider->setValue(song.GetVolume( ));
  VolumeSlider->setFixedHeight(28);
  VolumeSlider->setStyleSheet(R"(
    QSlider#volumeSlider::groove:horizontal{
      border-radius: 4px;
      height: 8px;
      background: #414141;
    }
    QSlider#volumeSlider::handle:horizontal{
      background: #78AB70;
      border: 4px solid #414141;
      width: 14px;
      height: 14px;
      margin: -7px 0;
      border-radius: 10px;
      padding: -8px 0;
    }
    QSlider#volumeSlider::sub-page:horizontal{
      background: #78AB70;
      border-radius: 4px;
      height: 8px;
    }
  )");
  VolumeSlider->setCursor(Qt::PointingHandCursor);

  connect(VolumeSlider, &QSlider::valueChanged, [this, VolumeSlider]( ) {
    song.SetVolume(VolumeSlider->value( ));
    });

  rightLayout->addWidget(VolumeSlider);

  //Fullscreen button
  QPushButton* FullscreenToggle = new QPushButton( );
  FullscreenToggle->setObjectName("fullscreenToggle");
  FullscreenToggle->setStyleSheet(R"(
    QPushButton#fullscreenToggle{
      background: transparent;
      border: 4px solid #414141;
      border-radius: 8px;
      margin-right: 14px;
    }
  )");
  FullscreenToggle->setFixedSize(50, 36);
  FullscreenToggle->setCursor(Qt::PointingHandCursor);
  connect(FullscreenToggle, &QPushButton::clicked, [ ]( ) {
    QMainWindow* mw = (QMainWindow*)QApplication::activeWindow( );
    if (mw->isFullScreen( ))
      mw->showNormal( );
    else
      mw->showFullScreen( );
    });
  QLabel* FullscreenLabel = new QLabel( );
  FullscreenLabel->setFixedSize(36, 24);
  FullscreenLabel->setObjectName("fullscreenLabel");
  FullscreenLabel->setPixmap(QPixmap(":icons/arrow-expand.svg").scaled(QSize(24, 24), Qt::IgnoreAspectRatio));

  QVBoxLayout* FullscreenLayout = new QVBoxLayout( );
  FullscreenLayout->setAlignment(Qt::AlignCenter);
  FullscreenLayout->addWidget(FullscreenLabel);

  QGraphicsColorizeEffect* colorize2 = new QGraphicsColorizeEffect( );
  colorize2->setColor(QColor("#83BFC8"));
  colorize2->setStrength(1);
  FullscreenLabel->setGraphicsEffect(colorize2);
  FullscreenToggle->setLayout(FullscreenLayout);

  rightLayout->addWidget(FullscreenToggle);

  mainLayout->addLayout(leftLayout, 0);
  mainLayout->addLayout(centerLayout, 1);
  mainLayout->addLayout(rightLayout, 0);

  // Some spacing in case the window is small enough to have the items touch
  mainLayout->setSpacing(10);

  this->setLayout(mainLayout);
}

FloatingControls::~FloatingControls( ) { }
