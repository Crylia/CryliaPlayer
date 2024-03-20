#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QLayout>
#include <QPixmap>
#include <filesystem>

#include "Modules/FloatingControls/FloatingControls.h"
#include "Layouts/QOverlayout.h"
#include "Modules/PageNavigator/pages.h"
#include "Pages/Playlist/PlaylistPage.h"
#include "Modules/PlaylistNavigator/PlaylistWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    MainWindow(std::filesystem::path path, QWidget* parent = nullptr);
    ~MainWindow( );

private:
    // In case the program gets started with a song as an argument
    std::filesystem::path path;

    void setupMainWindow( );
};
