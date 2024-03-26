#include "PlaylistPage.h"

PlaylistPage::PlaylistPage(QWidget* parent)
  : QFrame(parent) {

  setStyleSheet(R"(
    background-color: #2828ff;
    border-radius: 12px;
  )");

  applyShadow(this);
}

PlaylistPage::~PlaylistPage( ) { }
