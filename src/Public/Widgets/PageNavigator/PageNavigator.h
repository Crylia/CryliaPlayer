#pragma once

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QFont>
#include <QPushButton>

class PageNavigator :public QPushButton {
  Q_OBJECT
private:
  QLabel* m_text;
  QLabel* m_icon;

public:
  PageNavigator(QString text, QString icon, QWidget* parent = nullptr);

  void unselect( );
  void select( );
};
