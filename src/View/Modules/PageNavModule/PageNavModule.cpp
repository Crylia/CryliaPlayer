#include "PageNavModule.h"

PageNavModule::PageNavModule(QWidget* parent) :
  QFrame(parent),
  home(new PageNavigator(new HomePage( ), "Home", ":icons/home-outline.svg", "#81D4FA")),
  localFiles(new PageNavigator(new LocalFolderPage( ), "Local Files", ":icons/folder-outline.svg", "#FFE082")),
  playlist(new PageNavigator(new PlaylistPage( ), "Playlist", ":icons/magnify.svg", "#CE93D8")),
  settings(new PageNavigator(new SettingsPage( ), "Settings", ":icons/magnify.svg", "#C5E1A5")) {

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

  home->select( );

  PageManager& pageManager = PageManager::getInstance( );
  connect(home, &PageNavigator::SelectedChanged, [&pageManager, this](Page* page) {
    home->select( );
    localFiles->unselect( );
    playlist->unselect( );
    settings->unselect( );
    emit pageManager.ActivePageChanged(page);
    });
  connect(localFiles, &PageNavigator::SelectedChanged, [&pageManager, this](Page* page) {
    home->unselect( );
    localFiles->select( );
    playlist->unselect( );
    settings->unselect( );
    emit pageManager.ActivePageChanged(page);
    });
  connect(playlist, &PageNavigator::SelectedChanged, [&pageManager, this](Page* page) {
    home->unselect( );
    localFiles->unselect( );
    playlist->select( );
    settings->unselect( );
    emit pageManager.ActivePageChanged(page);
    });
  connect(settings, &PageNavigator::SelectedChanged, [&pageManager, this](Page* page) {
    home->unselect( );
    localFiles->unselect( );
    playlist->unselect( );
    settings->select( );
    emit pageManager.ActivePageChanged(page);
    });
}

PageNavModule::~PageNavModule( ) { }
