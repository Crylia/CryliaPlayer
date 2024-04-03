#pragma once

#include <QFrame>

class Page : public QFrame {

  Q_OBJECT

private:

public:
  Page(QWidget* parent = nullptr) :QFrame(parent) { }
  virtual ~Page( ) { }

  virtual std::string GetName( ) = 0;
};
