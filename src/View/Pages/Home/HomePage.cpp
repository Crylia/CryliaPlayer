#include "HomePage.h"

HomePage::HomePage(QWidget* parent)
  : QFrame(parent) {

  setStyleSheet(R"(
      background-color: #28FF28;
      border-radius: 12px;
  )");

  applyShadow(this);
}

HomePage::~HomePage( ) { }
