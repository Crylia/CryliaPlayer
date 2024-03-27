#include <iostream>

#include "FloatingControls.h"


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

FloatingControls::FloatingControls(QWidget* parent) :
  QFrame(parent),
  fullscreen(false),
  songRepeat(NONE) {

#pragma region Frame setup
  this->setFixedHeight(100);
  this->setObjectName("main");
  this->setStyleSheet(R"(
    QFrame#main{
      background-color:rgba(40, 40 ,40, 0.8);
      border: 4px solid #414141;
      border-radius: 12px;
      margin: 0px 10px 10px 10px;
    }
  )");
  applyShadow(this);
#pragma endregion

  /* Main Layout to store the Left Center and right controls */
  QHBoxLayout* mainLayout = new QHBoxLayout(this);

  /* Left side Icon, Artist and Song info */
  QHBoxLayout* leftLayout = new QHBoxLayout( );
  leftLayout->setSpacing(10);
  leftLayout->setAlignment(Qt::AlignLeft);

#pragma region Album Art
  m_albumArt = new QLabel( );
  m_albumArt->setObjectName("m_albumArt");
  m_albumArt->setAlignment(Qt::AlignCenter);
  m_albumArt->setStyleSheet(R"(
    QLabel#m_albumArt{
      border: 0px;
    }
  )");
  /* connect(m_albumArt, &QLabel::pixmapChanged, ()[ ] {
    m_albumArt->setStyleSheet(R"(
    QLabel#m_albumArt{
      border: 4px solid #414141;
      border-radius: 8px;
    }
  )");
    }); */
  leftLayout->addWidget(m_albumArt);
#pragma endregion

#pragma region Artist and Song name layout
  QVBoxLayout* artistSongLayout = new QVBoxLayout( );

#pragma region Artist Label
  m_artist = new QLabel( );
  m_artist->setMinimumWidth(50);
  m_artist->setObjectName("m_artist");
  m_artist->setStyleSheet(R"(
    QLabel#artist{
      font-size: 16px;
      font-weight: bold;
      color: #E1E1E1;
    }
  )");
#pragma endregion

#pragma region Song Title
  m_title = new QLabel( );
  m_title->setMinimumWidth(50);
  m_title->setObjectName("m_title");
  m_title->setStyleSheet(R"(
    QLabel#songName{
      font-size: 14px;
      color: #D7D7D7;
    }
  )");
#pragma endregion

  artistSongLayout->addWidget(m_artist);
  artistSongLayout->addWidget(m_title);
  leftLayout->addLayout(artistSongLayout);
#pragma endregion

#pragma region Center layout to store the song controls and pos bar

  QVBoxLayout* centerLayout = new QVBoxLayout( );
  centerLayout->setAlignment(Qt::AlignCenter);

  QHBoxLayout* songControlsLayout = new QHBoxLayout( );
  songControlsLayout->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

#pragma region Create Control Buttons
  m_shuffle = makeSongControlButton("shuffle", QSize(36, 36), "#757575");
  connect(m_shuffle, &QPushButton::clicked, [this]( ) {
    setShuffle(!musicPlayer.GetShuffle( ));
    });
  songControlsLayout->addWidget(m_shuffle);
  m_skipPrev = makeSongControlButton("prevSong", QSize(36, 36), "#D7D7D7");
  songControlsLayout->addWidget(m_skipPrev);
  m_playPause = makeSongControlButton("play", QSize(36, 36), "#D7D7D7");
  songControlsLayout->addWidget(m_playPause);
  m_skipNext = makeSongControlButton("nextSong", QSize(36, 36), "#D7D7D7");
  songControlsLayout->addWidget(m_skipNext);
  m_loop = makeSongControlButton("songRepeat", QSize(36, 36), "#757575");
  songControlsLayout->addWidget(m_loop);
#pragma endregion

  centerLayout->addLayout(songControlsLayout);

  QHBoxLayout* songScrollerLayout = new QHBoxLayout( );
  songScrollerLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

#pragma region Song Position
  m_songPos = new QLabel("-:--");
  m_songPos->setObjectName("m_songPos");
  m_songPos->setStyleSheet(R"(
    QLabel#m_songPos{
      font-size: 14px;
      color: #D7D7D7;
    }
  )");
  m_songPos->setAlignment(Qt::AlignRight);
#pragma endregion

#pragma region Song Duration
  m_songDur = new QLabel("-:--");
  m_songDur->setObjectName("m_songDur");
  m_songDur->setStyleSheet(R"(
    QLabel#m_songDur{
      font-size: 14px;
      color: #D7D7D7;
    }
  )");
#pragma endregion

#pragma region Song Progress Bar
  m_songProgress = new QSlider(Qt::Horizontal);
  m_songProgress->setObjectName("m_songProgress");
  m_songProgress->setRange(0, 100);
  m_songProgress->setValue(50);
  m_songProgress->setFixedHeight(28);
  m_songProgress->setStyleSheet(R"(
    QSlider#m_songProgress::groove:horizontal{
      border-radius: 4px;
      height: 8px;
      background: #414141;
    }
    QSlider#m_songProgress::handle:horizontal{
      background: #78AB70;
      border: 4px solid #414141;
      width: 14px;
      height: 14px;
      margin: -7px 0;
      border-radius: 10px;
      padding: -8px 0;
    }
    QSlider#m_songProgress::sub-page:horizontal{
      background: #78AB70;
      border-radius: 4px;
      height: 8px;
    }
  )");
  m_songProgress->setCursor(Qt::PointingHandCursor);
#pragma endregion

  songScrollerLayout->addWidget(m_songPos);
  songScrollerLayout->addWidget(m_songProgress);
  songScrollerLayout->addWidget(m_songDur);

  centerLayout->addLayout(songScrollerLayout);

#pragma endregion

#pragma region Right side layout to store the volume and fullscreen controls
  QHBoxLayout* rightLayout = new QHBoxLayout( );
  rightLayout->setAlignment(Qt::AlignRight);

#pragma region Volume Icon
  m_volumeIcon = new QLabel( );
  m_volumeIcon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  m_volumeIcon->setObjectName("m_volumeIcon");
  m_volumeIcon->setPixmap(RenderSvg(":icons/volume-high.svg", 36, 36).scaled(QSize(24, 24), Qt::IgnoreAspectRatio));
  QGraphicsColorizeEffect* colorize = new QGraphicsColorizeEffect( );
  colorize->setColor(QColor("#78AB70"));
  colorize->setStrength(1);
  m_volumeIcon->setGraphicsEffect(colorize);
  rightLayout->addWidget(m_volumeIcon);
#pragma endregion

#pragma region Volume Slider
  m_volumeSlider = new QSlider(Qt::Horizontal);
  m_volumeSlider->setObjectName("m_volumeSlider");
  m_volumeSlider->setRange(0, 128);
  m_volumeSlider->setValue(50);
  m_volumeSlider->setFixedHeight(28);
  m_volumeSlider->setStyleSheet(R"(
    QSlider#m_volumeSlider::groove:horizontal{
      border-radius: 4px;
      height: 8px;
      background: #414141;
    }
    QSlider#m_volumeSlider::handle:horizontal{
      background: #78AB70;
      border: 4px solid #414141;
      width: 14px;
      height: 14px;
      margin: -7px 0;
      border-radius: 10px;
      padding: -8px 0;
    }
    QSlider#m_volumeSlider::sub-page:horizontal{
      background: #78AB70;
      border-radius: 4px;
      height: 8px;
    }
  )");
  m_volumeSlider->setCursor(Qt::PointingHandCursor);
#pragma endregion

  rightLayout->addWidget(m_volumeSlider);

#pragma region Fullscreen Button
  m_fullscreen = new QPushButton( );
  m_fullscreen->setObjectName("m_fullscreen");
  m_fullscreen->setStyleSheet(R"(
    QPushButton#m_fullscreen{
      background: transparent;
      border: 4px solid #414141;
      border-radius: 8px;
    }
  )");
  m_fullscreen->setFixedSize(36, 36);
  m_fullscreen->setCursor(Qt::PointingHandCursor);
  connect(m_fullscreen, &QPushButton::clicked, [ ]( ) {
    QMainWindow* mw = (QMainWindow*)QApplication::activeWindow( );
    if (mw->isFullScreen( ))
      mw->showNormal( );
    else
      mw->showFullScreen( );
    });
  QLabel* FullscreenLabel = new QLabel( );
  FullscreenLabel->setObjectName("fullscreenLabel");
  FullscreenLabel->setPixmap(QPixmap(":icons/arrow-expand.svg").scaled(QSize(24, 24), Qt::IgnoreAspectRatio));

  QVBoxLayout* FullscreenLayout = new QVBoxLayout( );
  FullscreenLayout->setAlignment(Qt::AlignCenter);
  FullscreenLayout->addWidget(FullscreenLabel);

  FullscreenLabel->setGraphicsEffect([ ]( ) {
    QGraphicsColorizeEffect* color = new QGraphicsColorizeEffect( );
    color->setColor(QColor("#83BFC8"));
    color->setStrength(1);
    return color;
    }());
  m_fullscreen->setLayout(FullscreenLayout);
#pragma endregion

  rightLayout->addWidget(m_fullscreen);
  rightLayout->addSpacing(14);

#pragma endregion

  mainLayout->addLayout(leftLayout, 0);
  mainLayout->addLayout(centerLayout, 1);
  mainLayout->addLayout(rightLayout, 0);

  // Some spacing in case the window is small enough to have the items touch
  mainLayout->setSpacing(10);

  this->setLayout(mainLayout);
}

FloatingControls::~FloatingControls( ) { }

void FloatingControls::setShuffle(bool shuffle) {
  musicPlayer.SetShuffle(shuffle);

  QGraphicsColorizeEffect* colorize = new QGraphicsColorizeEffect( );
  musicPlayer.GetShuffle( ) ? colorize->setColor(QColor("#CE93D8")) : colorize->setColor(QColor("#757575"));
  colorize->setStrength(1);
  m_shuffle->setGraphicsEffect(colorize);
}
