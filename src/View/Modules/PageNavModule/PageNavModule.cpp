#include "PageNavModule.h"

#include <QWidget>
#include <QFrame>

PageNavModule::PageNavModule(QWidget* parent) :QFrame(parent) {

  this->setStyleSheet(R"(
    background-color: #282828;
    border-radius: 12px;
  )");

  applyShadow(this);

  this->setFixedSize(300, 180);

  QVBoxLayout* layout = new QVBoxLayout(this);

  PageNavigator* home = new PageNavigator("Home", ":icons/home-outline.svg", "#81D4FA");
  PageNavigator* localFiles = new PageNavigator("Local Files", ":icons/folder-outline.svg", "#FFE082");
  PageNavigator* playlist = new PageNavigator("Playlist", ":icons/magnify.svg", "#CE93D8");

  layout->addWidget(home);
  layout->addWidget(localFiles);
  layout->addWidget(playlist);

  connect(home, &PageNavigator::SelectedChanged, this, &PageNavModule::SelectChanged);
  connect(localFiles, &PageNavigator::SelectedChanged, this, &PageNavModule::SelectChanged);
  connect(playlist, &PageNavigator::SelectedChanged, this, &PageNavModule::SelectChanged);
}

PageNavModule::~PageNavModule( ) { }
