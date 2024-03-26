#pragma once

#include "PageNavigator.h"

/*
  Singleton to handle PageNavigator widget selects
*/
class SelectHandler {
public:
  static SelectHandler* GetInstance( );

  ~SelectHandler( ) { }
  SelectHandler(const SelectHandler&) = delete;
  void operator=(const SelectHandler&) = delete;

  void setSelected(PageNavigator* newSelected);

  PageNavigator* getSelected( );

private:
  SelectHandler( ) { }

  static SelectHandler* instance;

  PageNavigator* selected = nullptr;
};

SelectHandler* SelectHandler::instance = nullptr;

SelectHandler* SelectHandler::GetInstance( ) {
  if (instance == nullptr)
    instance = new SelectHandler( );
  return instance;
}

void SelectHandler::setSelected(PageNavigator* newSelected) {
  if (!newSelected && (newSelected == selected))
    return;

  if (this->selected == nullptr) {
    this->selected = newSelected;
    selected->select( );
    return;
  }

  selected->unselect( );
  newSelected->select( );
  this->selected = newSelected;
}

PageNavigator* SelectHandler::getSelected( ) {
  return selected;
}
