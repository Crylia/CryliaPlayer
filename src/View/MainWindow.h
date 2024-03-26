#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QLayout>
#include <QPixmap>
#include <filesystem>

#include "MainWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    MainWindow(std::filesystem::path path, QWidget* parent = nullptr);
    ~MainWindow( );

private:
    MainWidget* mainWidget;

    void setupMainWindow( );
};
