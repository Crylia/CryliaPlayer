#include "PlaylistWidget.h"

PlaylistWidget::PlaylistWidget(QWidget* parent) : QFrame(parent) {

  this->setStyleSheet(R"(
    background-color: #282828;
    border-radius: 12px;
  )");

  this->setFixedWidth(300);

}

PlaylistWidget::~PlaylistWidget( ) { }
