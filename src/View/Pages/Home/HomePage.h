#pragma once

#include <QWidget>
#include <QFrame>
#include "../../Tools/SvgToPixmap.hpp"


class HomePage : public QFrame {
  Q_OBJECT
private:
  /* data */
public:
  HomePage(QWidget* parent = nullptr);
  ~HomePage( );
};
