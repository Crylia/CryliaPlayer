#include <QtWidgets>
#include <QLayout>

#include "mainwindow.h"
#include "FloatingControls.h"
#include "pages.h"
#include "QOverlayout.h"
#include "PlaylistPage.h"
#include "PlaylistWidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  this->resize(1920, 1080);
  this->setGeometry(this->x( ), this->y( ), 1920, 1080);

  QWidget* mw = new QWidget(this);
  mw->setContentsMargins(10, 10, 10, 10);

  QOverlayout* ol = new QOverlayout(mw);

  Pages* p = new Pages(mw);
  PlaylistPage* pp = new PlaylistPage(mw);
  PlaylistWidget* pw = new PlaylistWidget(mw);
  FloatingControls* fc = new FloatingControls(mw);

  QVBoxLayout* vbox = new QVBoxLayout(mw);
  vbox->addWidget(fc, 0, Qt::AlignBottom);

  QHBoxLayout* hbox = new QHBoxLayout(mw);
  QVBoxLayout* vbox2 = new QVBoxLayout(mw);
  vbox2->addWidget(p);
  vbox2->addWidget(pw);
  hbox->addLayout(vbox2);
  hbox->addWidget(pp);

  hbox->setSpacing(10);
  vbox2->setSpacing(10);

  ol->addItem(vbox);
  ol->addItem(hbox);

  mw->setLayout(ol);

  this->setCentralWidget(mw);
}

MainWindow::~MainWindow( ) { }
