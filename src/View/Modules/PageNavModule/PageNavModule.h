#pragma once

#include <QWidget>
#include <QVector>
#include <QFrame>
#include <QSizePolicy>

#include "../../Widgets/PageNavigator/PageNavigator.h"
#include "../../Tools/SvgToPixmap.hpp"
#include "../../Pages/Home/HomePage.h"
#include "../../Pages/Playlist/PlaylistPage.h"
#include "../../Pages/LocalFolder/LocalFolderPage.h"
#include "../../Pages/Settings/SettingsPage.h"
#include "../../../Controller/PageManager/PageManager.h"

class PageNavModule : public QFrame {
  Q_OBJECT
private:
  QVector<PageNavigator*>* pages;

  PageNavigator* home;
  PageNavigator* localFiles;
  PageNavigator* playlist;
  PageNavigator* settings;

public:
  PageNavModule(QWidget* parent = nullptr);
  ~PageNavModule( );

signals:
  void SelectChanged(Page* page);
};
