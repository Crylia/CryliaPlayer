#pragma once

#include <QLayout>
#include <QMainWindow>
#include <QPixmap>
#include <QVBoxLayout>
#include <QtWidgets>
#include <filesystem>
#include <memory>

#include "MainWidget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  MainWidget *mainWidget;

  void setupMainWindow();
};
