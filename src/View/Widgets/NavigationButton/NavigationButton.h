#pragma once

#include <QPushButton>
#include <QLabel>
#include <QString>

class NavigationButton : public QPushButton {
  Q_OBJECT
private:
  QLabel* m_icon;
  QLabel* m_name;
  QString* m_colorHex;

  static NavigationButton* m_selected;

public:
  static void setSelected(NavigationButton* newSelected);
  static NavigationButton* getSelected( );

  NavigationButton( );
  ~NavigationButton( );

signals:
  void unselected( );
  void selected( );

private slots:
  void select( );
  void unselect( );

};
