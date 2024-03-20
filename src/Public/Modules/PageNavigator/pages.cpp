#include "pages.h"

#include <QWidget>
#include <QFrame>

Pages::Pages(QWidget* parent) :QFrame(parent) {

  this->setStyleSheet(R"(
    background-color: #282828;
    border-radius: 12px;
  )");

  this->setFixedSize(300, 180);

  QVBoxLayout* layout = new QVBoxLayout(this);

  PageNavigator* home = new PageNavigator("Home", ":icons/home.svg");
  PageNavigator* localFiles = new PageNavigator("Local Files", ":icons/home.svg");
  PageNavigator* playlist = new PageNavigator("Playlist", ":icons/songControl/magnify.svg");


  layout->addWidget(home);
  layout->addWidget(localFiles);
  layout->addWidget(playlist);
}

Pages::~Pages( ) { }
