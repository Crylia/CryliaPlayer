#include "PlaylistPage.h"

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QLabel>

PlaylistPage::PlaylistPage(QWidget* parent) : QFrame(parent) {

  this->setStyleSheet(R"(
    background-color: #282828;
    border-radius: 12px;
  )");
}

PlaylistPage::~PlaylistPage( ) { }
