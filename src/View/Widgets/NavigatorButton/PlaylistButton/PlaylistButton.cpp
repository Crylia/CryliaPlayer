#include "PlaylistButton.h"

void PlaylistButton::Select( ) {
  setStyleSheet(R"(
    #NavButton{
      border: 4px solid )" + color + R"(;
      border-radius: 6px;
    }
    #Text{
        color: #E0E0E0;
      }
  )");
}

void PlaylistButton::Unselect( ) {
  setStyleSheet(R"(
    #NavButton{
      border: 4px solid #414141;
      border-radius: 6px;
    }
    #Text{
        color: #E0E0E0;
      }
  )");
}

PlaylistButton::PlaylistButton(QString text, QString color, QString path, Page* page, QWidget* parent = nullptr) :
  NavButton(text, color, path, page, parent) { }

PlaylistButton::~PlaylistButton( ) { }
