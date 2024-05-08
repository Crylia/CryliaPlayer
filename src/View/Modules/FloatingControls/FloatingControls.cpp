#include "FloatingControls.h"

static QPushButton *makeSongControlButton(QString name,
                                          QSize size = QSize(36, 36),
                                          QString color = "#D7D7D7") {
  QPushButton *button = new QPushButton();
  button->setObjectName(name);
  button->setStyleSheet(R"(
    QPushButton#)" + name +
                        R"({
      background-color: transparent;
      border: 0;
    }
  )");
  button->setIcon(RenderSvg(":/icons/" + name + ".svg", 36, 36));
  button->setIconSize(size);
  button->setCursor(Qt::PointingHandCursor);
  QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
  colorize->setColor(QColor(color));
  colorize->setStrength(1);
  button->setGraphicsEffect(colorize);

  return button;
}

FloatingControls::FloatingControls(QWidget *parent)
    : QFrame(parent), fullscreen(false) {

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
  QHBoxLayout *mainLayout = new QHBoxLayout(this);

  /* Left side Icon, Artist and Song info */
  QHBoxLayout *leftLayout = new QHBoxLayout();
  leftLayout->setSpacing(10);
  leftLayout->setAlignment(Qt::AlignLeft);

#pragma region Album Art
  m_albumArt = new QLabel();
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
  QVBoxLayout *artistSongLayout = new QVBoxLayout();

#pragma region Artist Label
  m_artist = new QLabel();
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
  m_title = new QLabel();
  m_title->setMinimumWidth(50);
  m_title->setObjectName("m_title");
  m_title->setStyleSheet(R"(
    QLabel#songName{
      font-size: 14px;
      color: #D7D7D7;
    }
  )");
  connect(&musicPlayer, &MusicPlayer::SongChanged, this,
          &FloatingControls::setTitle);
#pragma endregion

  artistSongLayout->addWidget(m_artist);
  artistSongLayout->addWidget(m_title);
  leftLayout->addLayout(artistSongLayout);
#pragma endregion

#pragma region Center layout to store the song controls and pos bar

  QVBoxLayout *centerLayout = new QVBoxLayout();
  centerLayout->setAlignment(Qt::AlignCenter);

  QHBoxLayout *songControlsLayout = new QHBoxLayout();
  songControlsLayout->setAlignment(Qt::AlignCenter | Qt::AlignBottom);

#pragma region Create Control Buttons
  m_shuffle = makeSongControlButton("shuffle", QSize(36, 36), "#757575");
  connect(m_shuffle, &QPushButton::clicked,
          [this]() { setShuffle(!musicPlayer.GetShuffle()); });
  songControlsLayout->addWidget(m_shuffle);
  m_skipPrev = makeSongControlButton("prevSong", QSize(36, 36), "#D7D7D7");
  songControlsLayout->addWidget(m_skipPrev);
  m_playPause = makeSongControlButton("play", QSize(36, 36), "#D7D7D7");
  connect(m_playPause, &QPushButton::clicked, this,
          &FloatingControls::playPause);
  songControlsLayout->addWidget(m_playPause);
  m_skipNext = makeSongControlButton("nextSong", QSize(36, 36), "#D7D7D7");
  songControlsLayout->addWidget(m_skipNext);
  m_loop = makeSongControlButton("songRepeat", QSize(36, 36), "#757575");
  connect(m_loop, &QPushButton::clicked, [this]() {
    switch (musicPlayer.GetLoop()) {
    case Loop::None:
      setLoop(Loop::All);
      break;
    case Loop::All:
      setLoop(Loop::Once);
      break;
    case Loop::Once:
      setLoop(Loop::None);
      break;
    }
  });
  songControlsLayout->addWidget(m_loop);
#pragma endregion

  centerLayout->addLayout(songControlsLayout);

  QHBoxLayout *songScrollerLayout = new QHBoxLayout();
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
  connect(&musicPlayer, &MusicPlayer::SongChanged, this,
          &FloatingControls::setSongDur);
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
  QHBoxLayout *rightLayout = new QHBoxLayout();
  rightLayout->setAlignment(Qt::AlignRight);

#pragma region Volume Icon
  m_volumeIcon = new QLabel();
  m_volumeIcon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  m_volumeIcon->setObjectName("m_volumeIcon");
  m_volumeIcon->setPixmap(RenderSvg(":icons/volume-medium.svg", 24, 24));
  QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
  colorize->setColor(QColor("#FFF59D"));
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
      background: #FFF59D;
      border: 4px solid #414141;
      width: 14px;
      height: 14px;
      margin: -7px 0;
      border-radius: 10px;
      padding: -8px 0;
    }
    QSlider#m_volumeSlider::sub-page:horizontal{
      background: #FFF59D;
      border-radius: 4px;
      height: 8px;
    }
  )");
  m_volumeSlider->setCursor(Qt::PointingHandCursor);
  connect(m_volumeSlider, &QSlider::valueChanged, this,
          &FloatingControls::volumeChanged);
#pragma endregion

  rightLayout->addWidget(m_volumeSlider);

#pragma region Fullscreen Button
  m_fullscreen = new QPushButton();
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
  connect(m_fullscreen, &QPushButton::clicked, []() {
    QMainWindow *mw = (QMainWindow *)QApplication::activeWindow();
    if (mw->isFullScreen())
      mw->showNormal();
    else
      mw->showFullScreen();
  });
  QLabel *FullscreenLabel = new QLabel();
  FullscreenLabel->setObjectName("fullscreenLabel");
  FullscreenLabel->setPixmap(QPixmap(":icons/arrow-expand.svg")
                                 .scaled(QSize(24, 24), Qt::IgnoreAspectRatio));

  QVBoxLayout *FullscreenLayout = new QVBoxLayout();
  FullscreenLayout->setAlignment(Qt::AlignCenter);
  FullscreenLayout->addWidget(FullscreenLabel);

  FullscreenLabel->setGraphicsEffect([]() {
    QGraphicsColorizeEffect *color = new QGraphicsColorizeEffect();
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

  m_progressUpdateTimer = new QTimer();
  connect(m_progressUpdateTimer, &QTimer::timeout, this, [this]() {
    if (!musicPlayer.IsActive()) {
      m_songProgress->setValue(0);
      m_songPos->setText("-:--");
      return;
    }

    u_short sec = musicPlayer.GetSongProgression();

    m_songPos->setText(QTime(0, sec / 60, sec % 60).toString("mm:ss"));

    m_songProgress->setValue(sec);
  });
  m_progressUpdateTimer->start(1000);
}

FloatingControls::~FloatingControls() {}

void FloatingControls::setShuffle(bool shuffle) {
  musicPlayer.SetShuffle(shuffle);

  QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
  // Get the value to make sure it actually changed
  musicPlayer.GetShuffle() ? colorize->setColor(QColor("#CE93D8"))
                           : colorize->setColor(QColor("#757575"));
  colorize->setStrength(1);
  m_shuffle->setGraphicsEffect(colorize);
}

void FloatingControls::volumeChanged() {
  int value = m_volumeSlider->value();
  musicPlayer.SetVolume(value);

  // We know MIX_MAX_VOLUME is always 0-128 so no need to calculate anything
  if (value == 0) {
    m_volumeIcon->setPixmap(RenderSvg(":icons/volume-off.svg", 24, 24));
    QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
    colorize->setColor(QColor("#FFF59D"));
    colorize->setStrength(1);
    m_volumeIcon->setGraphicsEffect(colorize);
  } else if (value > 0 && value < 42) {
    m_volumeIcon->setPixmap(RenderSvg(":icons/volume-low.svg", 24, 24));
    QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
    colorize->setColor(QColor("#FFF59D"));
    colorize->setStrength(1);
    m_volumeIcon->setGraphicsEffect(colorize);
  } else if (value >= 42 && value < 84) {
    m_volumeIcon->setPixmap(RenderSvg(":icons/volume-medium.svg", 24, 24));
    QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
    colorize->setColor(QColor("#FFF59D"));
    colorize->setStrength(1);
    m_volumeIcon->setGraphicsEffect(colorize);
  } else if (value >= 84 && value < 128) {
    m_volumeIcon->setPixmap(RenderSvg(":icons/volume-high.svg", 24, 24));
    QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
    colorize->setColor(QColor("#FFF59D"));
    colorize->setStrength(1);
    m_volumeIcon->setGraphicsEffect(colorize);
  }
}

void FloatingControls::setLoop(Loop loop) {
  musicPlayer.SetLoop(loop);

  QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
  // Get the value to make sure it actually changed
  switch (musicPlayer.GetLoop()) {
  case Loop::None:
    m_loop->setIcon(RenderSvg(":icons/songRepeat.svg", 36, 36));
    colorize->setColor(QColor("#757575"));
    colorize->setStrength(1);
    m_loop->setGraphicsEffect(colorize);
    break;
  case Loop::All:
    m_loop->setIcon(RenderSvg(":icons/songRepeat.svg", 36, 36));
    colorize->setColor(QColor("#CE93D8"));
    colorize->setStrength(1);
    m_loop->setGraphicsEffect(colorize);
    break;
  case Loop::Once:
    m_loop->setIcon(RenderSvg(":icons/repeat-once.svg", 36, 36));
    colorize->setColor(QColor("#CE93D8"));
    colorize->setStrength(1);
    m_loop->setGraphicsEffect(colorize);
    break;
  }
}

void FloatingControls::playPause() {
  //! TESTING ONLY
  musicPlayer.PlaySong(std::make_unique<Song>(
      "Check This Out", "", "2Complex", "", "", "", "", "", "", "", "", "",
      "/home/crylia/Musik/Dubstep EDM Electro/2Complex - Check This Out.mp3",
      0));

  bool playing = musicPlayer.IsPlaying();

  QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
  playing ? m_playPause->setIcon(RenderSvg(":icons/play.svg", 36, 36))
          : m_playPause->setIcon(RenderSvg(":icons/pause.svg", 36, 36));
  colorize->setColor(QColor("#D7D7D7"));
  colorize->setStrength(1);
  m_playPause->setGraphicsEffect(colorize);
}

void FloatingControls::setTitle() {
  m_title->setText(musicPlayer.GetCurrentlyPlaying()->title());
  m_artist->setText(musicPlayer.GetCurrentlyPlaying()->artist());

  m_albumArt->setPixmap(musicPlayer.GetAlbumArt());
  QRect targetRect;
  if (m_albumArt->pixmap().width() > m_albumArt->pixmap().height()) {
    int sideLength = m_albumArt->pixmap().height();
    targetRect = QRect((m_albumArt->pixmap().width() - sideLength) / 2, 0,
                       sideLength, sideLength);
  } else {
    int sideLength = m_albumArt->pixmap().width();
    targetRect = QRect(0, (m_albumArt->pixmap().height() - sideLength) / 2,
                       sideLength, sideLength);
  }

  m_albumArt->setPixmap(m_albumArt->pixmap()
                            .copy(targetRect)
                            .scaled(QSize(64, 64), Qt::KeepAspectRatio));
}

void FloatingControls::setSongDur() {
  u_short sec = musicPlayer.GetSongDuration();

  m_songDur->setText(QTime(0, sec / 60, sec % 60).toString("mm:ss"));
}
