#include "pages.h"

#include <QWidget>
#include <QFrame>

Pages::Pages(QWidget* parent) :QFrame(parent) {

  this->setStyleSheet(R"(
    background-color: #282828;
    border-radius: 12px;
  )");

  this->setFixedSize(300, 180);
}

Pages::~Pages( ) { }
