#include "MainWindow.h"

void MainWindow::setupMainWindow( ) {
  this->setWindowTitle("Crylia Player");
  this->setWindowIcon(QIcon(":aqua.jpg"));

  setObjectName("MainWindow");
  setStyleSheet(R"(
    #MainWindow{
      background-color: #121212;
    }
  )");

  this->setCentralWidget(mainWidget);
}

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), mainWidget(new MainWidget(this)) {
  setupMainWindow( );
}

MainWindow::~MainWindow( ) { }
