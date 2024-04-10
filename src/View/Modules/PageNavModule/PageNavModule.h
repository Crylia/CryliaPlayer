#pragma once

#include <QWidget>
#include <QVector>
#include <QFrame>
#include <QSizePolicy>
#include <QVBoxLayout>

#include "../../Widgets/NavigatorButton/NavButton.h"
#include "../../Widgets/NavigatorButton/PageButton/PageButton.h"
#include "../../Tools/SvgToPixmap.hpp"
#include "../../Pages/Home/HomePage.h"
#include "../../Pages/Playlist/PlaylistPage.h"
#include "../../Pages/LocalFolder/LocalFolderPage.h"
#include "../../Pages/Settings/SettingsPage.h"
#include "../../../Controller/PageManager/PageManager.h"

class PageNavModule : public QFrame {
  Q_OBJECT
private:
  QVector<NavButton*>* pages;

  NavButton* home;
  NavButton* localFiles;
  NavButton* playlist;
  NavButton* settings;

public:
  PageNavModule(QWidget* parent = nullptr);
  ~PageNavModule( );

signals:
  void SelectChanged(Page* page);
};
