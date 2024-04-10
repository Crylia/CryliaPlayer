#include "PlaylistPage.h"

PlaylistPage::PlaylistPage(QWidget* parent) :Page(parent) {

  setStyleSheet(R"(
    background-color: #282828;
    border-radius: 12px;
  )");

  applyShadow(this);
}

PlaylistPage::~PlaylistPage( ) { }
