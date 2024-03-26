#pragma once

#include <QWidget>
#include <QLayout>
#include <filesystem>
#include <QStackedLayout>

#include "Layouts/QOverlayout.h"
#include "Modules/FloatingControls/FloatingControls.h"
#include "Modules/PageNavModule/PageNavModule.h"
#include "Modules/PlaylistNavModule/PlaylistNavModule.h"
#include "Pages/Playlist/PlaylistPage.h"
#include "Pages/Home/HomePage.h"

class MainWidget : public QWidget {
  Q_OBJECT
private:

  PageNavModule* pageNav;
  PlaylistNavModule* playlistNav;

  PlaylistPage* playlistPage;
  HomePage* homePage;

  FloatingControls* floatingControlls;

  void setupMainWidget( );

public:
  MainWidget(QWidget* parent = nullptr);
  MainWidget(std::filesystem::path path, QWidget* parent = nullptr);
  ~MainWidget( );

private slots:
  void PageChangedAction( );


};
