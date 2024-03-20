#pragma once

#include <QPixmap>
#include <QString>
#include <QSvgRenderer>
#include <QPainter>

static QPixmap RenderSvg(QString path, int w, int h) {
  QSvgRenderer renderer(path);
  QPixmap pixmap(w, h);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);
  renderer.render(&painter);

  return pixmap;
}
