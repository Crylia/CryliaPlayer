#pragma once

#include <QObject>

#include "../../View/Pages/Page.h"

class PageManager : public QObject {
  Q_OBJECT
public:
  static PageManager& getInstance( ) {
    static PageManager instance;
    return instance;
  }

private:
  PageManager( ) { }

  Page* activePage = nullptr;
public:
  ~PageManager( );

  PageManager(PageManager const&) = delete;
  void operator=(PageManager const&) = delete;

  void SetActivePage(Page* page) { activePage = page; }
  Page* GetActivePage( ) { return activePage; }

signals:
  void ActivePageChanged(Page* page);
};
