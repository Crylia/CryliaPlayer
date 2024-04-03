#include "PlaylistPage.h"

PlaylistPage::PlaylistPage(QWidget* parent) :Page(parent) {

  setStyleSheet(R"(
    background-color: #2828ff;
    border-radius: 12px;
  )");

  applyShadow(this);
}

PlaylistPage::~PlaylistPage( ) { }
