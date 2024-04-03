#include "MainWidget.h"

void MainWidget::setupMainWidget( ) {
  setContentsMargins(10, 10, 10, 10);
  QOverlayout* ol = new QOverlayout(this);
  setLayout(ol);

  QVBoxLayout* vbox = new QVBoxLayout( );
  floatingControlls = new FloatingControls(this);
  vbox->addWidget(floatingControlls, 0, Qt::AlignBottom);

  QHBoxLayout* hbox = new QHBoxLayout( );
  QVBoxLayout* vbox2 = new QVBoxLayout( );
  vbox2->addWidget(pageNav);
  vbox2->addWidget(playlistNav);
  hbox->addLayout(vbox2);
  QHBoxLayout* stackedLayout = new QHBoxLayout( );
  stackedLayout->addWidget(homePage);
  stackedLayout->addWidget(playlistPage);
  stackedLayout->addWidget(localFolderPage);

  pageManager.GetActivePage( )->setVisible(true);
  playlistPage->setVisible(false);
  localFolderPage->setVisible(false);

  hbox->addLayout(stackedLayout, 0);

  hbox->setSpacing(10);
  vbox2->setSpacing(10);

  ol->addItem(hbox);
  ol->addItem(vbox);

  connect(&pageManager, &PageManager::ActivePageChanged, [this, stackedLayout](Page* page) {
    if (page->GetName( ) == "home") {
      stackedLayout->itemAt(0)->widget( )->setVisible(true);
      stackedLayout->itemAt(1)->widget( )->setVisible(false);
      stackedLayout->itemAt(2)->widget( )->setVisible(false);
    }
    else if (page->GetName( ) == "playlist") {
      stackedLayout->itemAt(0)->widget( )->setVisible(false);
      stackedLayout->itemAt(1)->widget( )->setVisible(true);
      stackedLayout->itemAt(2)->widget( )->setVisible(false);
    }
    else if (page->GetName( ) == "localFolder") {
      stackedLayout->itemAt(0)->widget( )->setVisible(false);
      stackedLayout->itemAt(1)->widget( )->setVisible(false);
      stackedLayout->itemAt(2)->widget( )->setVisible(true);
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
  localFolderPage(new LocalFolderPage(this)) {
  pageManager.SetActivePage(homePage);
  setupMainWidget( );
}

MainWidget::~MainWidget( ) { }
