#pragma once

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QSvgRenderer>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

static QPixmap RenderSvg(QString path, int w, int h) {
  QSvgRenderer renderer(path);
  QPixmap pixmap(w, h);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);
  renderer.render(&painter);

  return pixmap;
}

template <typename T>
static void applyShadow(T obj, int blurRadius = 20, int xOffset = 10, int yOffset = 10, QString color = "#000000", int offset = 2) {
  QGraphicsDropShadowEffect* dropShadow = new QGraphicsDropShadowEffect( );
  dropShadow->setBlurRadius(blurRadius);
  dropShadow->setXOffset(xOffset);
  dropShadow->setYOffset(yOffset);
  dropShadow->setColor(color);
  dropShadow->setOffset(offset);
  obj->setGraphicsEffect(dropShadow);
}
