#include "PageButton.h"

PageButton::PageButton(QString text, QString color, QString path, Page* page, QWidget* parent = nullptr) :
  NavButton(text, color, path, page, parent) { }

PageButton::~PageButton( ) { }


void PageButton::Select( ) {
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

void PageButton::Unselect( ) {
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
