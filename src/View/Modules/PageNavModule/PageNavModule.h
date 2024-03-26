#pragma once

#include <QWidget>
#include <QVector>
#include <QFrame>
#include "../../Widgets/PageNavigator/PageNavigator.h"
#include "../../Tools/SvgToPixmap.hpp"

class PageNavModule : public QFrame {
  Q_OBJECT
private:
  QVector<PageNavigator> pages;

public:
  PageNavModule(QWidget* parent = nullptr);
  ~PageNavModule( );

signals:
  void SelectChanged(PageNavigator* pn);
};
