#pragma once

#include <QWidget>
#include <QFrame>

class Pages : public QFrame {

  Q_OBJECT

private:
  //Page[3] pages;

public:
  Pages(QWidget* parent = nullptr);
  ~Pages( );
};
