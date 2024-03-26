#pragma once

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QFont>
#include <QPushButton>
#include <QColor>
#include <QGraphicsColorizeEffect>

class PageNavigator :public QPushButton {
  Q_OBJECT
private:
  QLabel* m_text;
  QLabel* m_icon;
  QString m_iconPath;
  QString m_color;

public:
  PageNavigator(QString text, QString icon, QString color, QWidget* parent = nullptr);

  void unselect( );
  void select( );

  QString GetText( );

signals:
  void SelectedChanged(PageNavigator* pn);
};
