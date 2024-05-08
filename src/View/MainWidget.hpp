#pragma once

#include <QLayout>
#include <QStackedLayout>
#include <QWidget>
#include <filesystem>

#include "../Controller/PageManager/PageManager.h"
#include "Layouts/QOverlayout.h"
#include "Modules/FloatingControls/FloatingControls.h"
#include "Modules/PageNavModule/PageNavModule.h"
#include "Modules/PlaylistNavModule/PlaylistNavModule.h"
#include "Pages/Home/HomePage.h"
#include "Pages/LocalFolder/LocalFolderPage.h"
#include "Pages/Playlist/PlaylistPage.h"
#include "Pages/Settings/SettingsPage.h"

class MainWidget : public QWidget {
  Q_OBJECT
private:
  PageNavModule *pageNav;
  PlaylistNavModule *playlistNav;

  PlaylistPage *playlistPage;
  HomePage *homePage;
  LocalFolderPage *localFolderPage;
  SettingsPage *settingsPage;

  FloatingControls *floatingControlls;

  PageManager &pageManager{PageManager::getInstance()};

  void setupMainWidget();

public:
  MainWidget(QWidget *parent = nullptr);
  ~MainWidget();

private slots:
  void PageChangedAction();
};
