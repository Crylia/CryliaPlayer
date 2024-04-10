#include "PageNavModule.h"

PageNavModule::PageNavModule(QWidget* parent) :
  QFrame(parent),
  home(new PageButton(QString("Home"), QString("#81D4FA"), QString(":icons/home-outline.svg"), new HomePage( ), this)),
  localFiles(new PageButton("Local Files", QString("#FFE082"), QString(":icons/folder-outline.svg"), new LocalFolderPage( ), this)),
  playlist(new PageButton("Playlist", QString("#CE93D8"), QString(":icons/magnify.svg"), new PlaylistPage( ), this)),
  settings(new PageButton("Settings", QString("#C5E1A5"), QString(":icons/magnify.svg"), new SettingsPage( ), this)) {

  this->setStyleSheet(R"(
    background-color: #282828;
    border-radius: 12px;
  )");

  applyShadow(this);

  this->setFixedSize(300, 240);

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(home);
  layout->addWidget(settings);
  layout->addWidget(localFiles);
  layout->addWidget(playlist);

  home->Select( );

  PageManager& pageManager = PageManager::getInstance( );
  connect(home, &NavButton::SelectedChanged, [&pageManager, this](Page* page) {
    home->Select( );
    localFiles->Unselect( );
    playlist->Unselect( );
    settings->Unselect( );
    emit pageManager.ActivePageChanged(page);
    });
  connect(localFiles, &NavButton::SelectedChanged, [&pageManager, this](Page* page) {
    home->Unselect( );
    localFiles->Select( );
    playlist->Unselect( );
    settings->Unselect( );
    emit pageManager.ActivePageChanged(page);
    });
  connect(playlist, &NavButton::SelectedChanged, [&pageManager, this](Page* page) {
    home->Unselect( );
    localFiles->Unselect( );
    playlist->Select( );
    settings->Unselect( );
    emit pageManager.ActivePageChanged(page);
    });
  connect(settings, &NavButton::SelectedChanged, [&pageManager, this](Page* page) {
    home->Unselect( );
    localFiles->Unselect( );
    playlist->Unselect( );
    settings->Select( );
    emit pageManager.ActivePageChanged(page);
    });
}

PageNavModule::~PageNavModule( ) { }
