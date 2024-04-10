#include "HomePage.h"

HomePage::HomePage(QWidget* parent) : Page(parent) {

  setStyleSheet(R"(
      background-color: #282828;
      border-radius: 12px;
  )");

  applyShadow(this);
}

HomePage::~HomePage( ) { }
