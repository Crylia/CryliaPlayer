#pragma once

#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QColor>
#include <QSvgRenderer>
#include <QPainter>
#include <QHBoxLayout>

#include "../../../View/Pages/Page.h"

class SquareIcon : public QLabel {
public:
  QSize sizeHint( ) const override {
    QSize hint = QLabel::sizeHint( );
    int side = qMin(hint.width( ), hint.height( ));
    return QSize(side, side);
  }
};

class NavButton : public QPushButton {
  Q_OBJECT
protected:
  QLabel* m_text;
  SquareIcon* m_icon;
  QString* m_color;

  Page* page;

  QString iconPath;
  QString color;
private:
  void setupButton( );
public:
  NavButton(QString, QString, QString, Page*, QWidget*);
  NavButton(QString, QString, QPixmap, Page*, QWidget*);
  ~NavButton( );

  void SetText(QString newText) { m_text->setText(newText); }
  QString GetText( ) { return m_text->text( ); }

  virtual void Select( ) = 0;
  virtual void Unselect( ) = 0;

signals:
  void SelectedChanged(Page* page);
};
