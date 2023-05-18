#pragma once

#include <QLayout>
#include <QList>
#include <QLayoutItem>

class QOverlayout : public QLayout {
private:
  QList<QLayoutItem*> list;
public:
  QOverlayout(QWidget* parent);
  ~QOverlayout( );

  void addItem(QLayoutItem* item) override;
  QSize sizeHint( ) const override;
  QSize minimumSize( ) const override;
  int count( ) const override;
  QLayoutItem* itemAt(int) const override;
  QLayoutItem* takeAt(int) override;
  void setGeometry(const QRect& rect) override;
};
