#pragma once

#include "../NavButton.h"

class PageButton : public NavButton {

public:
  PageButton(QString, QString, QString, Page*, QWidget*);
  PageButton(QString, QString, QPixmap, Page*, QWidget*);
  ~PageButton( );

  void Select( );
  void Unselect( );
};

