#include "MainWidget.h"

void MainWidget::setupMainWidget( ) {
  setContentsMargins(10, 10, 10, 10);

  QOverlayout* ol = new QOverlayout(this);
  setLayout(ol);

  QVBoxLayout* vbox = new QVBoxLayout( );
  vbox->addWidget(floatingControlls, 0, Qt::AlignBottom);

  QHBoxLayout* hbox = new QHBoxLayout( );
  QVBoxLayout* vbox2 = new QVBoxLayout( );
  vbox2->addWidget(pageNav);
  vbox2->addWidget(playlistNav);
  hbox->addLayout(vbox2);
  QHBoxLayout* stackedLayout = new QHBoxLayout( );

  stackedLayout->addWidget(homePage);
  stackedLayout->addWidget(playlistPage);

  playlistPage->setVisible(false);

  hbox->addLayout(stackedLayout, 0);

  hbox->setSpacing(10);
  vbox2->setSpacing(10);

  ol->addItem(hbox);
  ol->addItem(vbox);

  connect(pageNav, &PageNavModule::SelectChanged, [this, stackedLayout](PageNavigator* pn) {
    if (pn->GetText( ).toStdString( ) == "Home") {
      //stackedLayout->setCurrentIndex(0);
      stackedLayout->itemAt(0)->widget( )->setVisible(true);
      stackedLayout->itemAt(1)->widget( )->setVisible(false);
    }
    else if (pn->GetText( ).toStdString( ) == "Playlist") {
      //stackedLayout->setCurrentIndex(1);
      stackedLayout->itemAt(0)->widget( )->setVisible(false);
      stackedLayout->itemAt(1)->widget( )->setVisible(true);
    }
    });
}

void MainWidget::PageChangedAction( ) { }

MainWidget::MainWidget(QWidget* parent)
  : QWidget(parent),
  pageNav(new PageNavModule(this)),
  playlistNav(new PlaylistNavModule(this)),
  playlistPage(new PlaylistPage(this)),
  homePage(new HomePage(this)),
  floatingControlls(new FloatingControls(this)) {
  setupMainWidget( );
}

MainWidget::MainWidget(std::filesystem::path path, QWidget* parent)
  : QWidget(parent),
  pageNav(new PageNavModule(this)),
  playlistNav(new PlaylistNavModule(this)),
  playlistPage(new PlaylistPage(this)),
  homePage(new HomePage(this)),
  floatingControlls(new FloatingControls(this, path)) {
  setupMainWidget( );
}

MainWidget::~MainWidget( ) { }
