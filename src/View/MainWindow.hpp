#pragma once

#include <QLayout>
#include <QMainWindow>
#include <QPixmap>
#include <QVBoxLayout>
#include <QtWidgets>

#include "MainWidget.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  MainWidget *mainWidget;

  void setupMainWindow();
};
