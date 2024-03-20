#pragma once

#include <QWidget>
#include <QFrame>
#include "../../Widgets/PageNavigator/PageNavigator.h"

class Pages : public QFrame {

  Q_OBJECT

private:
  //Page[3] pages;

public:
  Pages(QWidget* parent = nullptr);
  ~Pages( );
};
