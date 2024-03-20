#include "MainWindow.h"

void MainWindow::setupMainWindow( ) {
  this->setWindowTitle("Crylia Player");
  this->setWindowIcon(QIcon(":aqua.jpg"));

  QWidget* mw = new QWidget(this);
  mw->setContentsMargins(10, 10, 10, 10);

  QOverlayout* ol = new QOverlayout(mw);
  mw->setLayout(ol);

  Pages* p = new Pages(mw);
  PlaylistPage* pp = new PlaylistPage(mw);
  PlaylistWidget* pw = new PlaylistWidget(mw);
  FloatingControls* fc = new FloatingControls(mw, this->path);

  QVBoxLayout* vbox = new QVBoxLayout( );
  vbox->addWidget(fc, 0, Qt::AlignBottom);

  QHBoxLayout* hbox = new QHBoxLayout( );
  QVBoxLayout* vbox2 = new QVBoxLayout( );
  vbox2->addWidget(p);
  vbox2->addWidget(pw);
  hbox->addLayout(vbox2);
  hbox->addWidget(pp);

  hbox->setSpacing(10);
  vbox2->setSpacing(10);

  ol->addItem(vbox);
  ol->addItem(hbox);

  this->setCentralWidget(mw);
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  setupMainWindow( );
}

MainWindow::MainWindow(std::filesystem::path path, QWidget* parent)
  : QMainWindow(parent), path(path) {
  setupMainWindow( );
}

MainWindow::~MainWindow( ) { }
