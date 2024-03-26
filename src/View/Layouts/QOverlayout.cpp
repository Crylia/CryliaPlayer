#include "QOverlayout.h"

#include <QLayout>
#include <QtWidgets>

int QOverlayout::count( )const {
  return list.size( );
}

QLayoutItem* QOverlayout::itemAt(int idx)const {
  return list.value(idx);
}

QLayoutItem* QOverlayout::takeAt(int idx) {
  return idx >= 0 && idx < list.size( ) ? list.takeAt(idx) : 0;
}

void QOverlayout::addItem(QLayoutItem* item) {
  list.append(item);
}

QOverlayout::QOverlayout(QWidget* parent) : QLayout(parent) { }

QOverlayout::~QOverlayout( ) {
  QLayoutItem* item;
  while ((item = takeAt(0)))
    delete item;
}

void QOverlayout::setGeometry(const QRect& r) {
  QLayout::setGeometry(r);

  if (list.size( ) == 0) return;

  int w = r.width( );
  int h = r.height( );

  int i = 0;
  while (i < list.size( )) {
    list.at(i)->setGeometry(QRect(r.x( ), r.y( ), w, h));
    ++i;
  }
}

QSize QOverlayout::sizeHint( ) const {
  QSize s(0, 0);
  int n = list.count( );
  if (n > 0)
    s = QSize(100, 70);
  int i = 0;
  while (i < n) {
    QLayoutItem* o = list.at(i);
    s = s.expandedTo(o->sizeHint( ));
    ++i;
  }
  return s;
}

QSize QOverlayout::minimumSize( ) const {
  QSize s(0, 0);
  int n = list.count( );

  int i = 0;
  while (i < n) {
    QLayoutItem* o = list.at(i);
    s = s.expandedTo(o->sizeHint( ));
    ++i;
  }

  return s;
}
