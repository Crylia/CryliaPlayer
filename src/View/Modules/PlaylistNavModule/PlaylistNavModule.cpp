#include "PlaylistNavModule.h"

PlaylistNavModule::PlaylistNavModule(QWidget* parent) : QFrame(parent) {

  this->setStyleSheet(R"(
    background-color: #282828;
    border-radius: 12px;
  )");

  this->setFixedWidth(300);

  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->addSpacing(10);

}

PlaylistNavModule::~PlaylistNavModule( ) { }
