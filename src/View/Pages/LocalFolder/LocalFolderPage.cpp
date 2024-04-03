#include "LocalFolderPage.h"

LocalFolderPage::LocalFolderPage(QWidget* parent) : Page(parent) {

  setStyleSheet(R"(
      background-color: #FF2828;
      border-radius: 12px;
  )");

  applyShadow(this);
}

LocalFolderPage::~LocalFolderPage( ) { }
