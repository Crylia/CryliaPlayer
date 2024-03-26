#pragma once

#include <iostream>

template<typename T>
class SongHistory {
private:
  struct Node {
    T data;
    Node* next;
  };

  Node* topNode = nullptr;

public:
  SongHistory( ) { }
  ~SongHistory( ) {
    while (!isEmpty( ))
      pop( );
  }

  void push(const T& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = topNode;
    topNode = newNode;
  }

  void pop( ) {
    if (!isEmpty( )) {
      Node* tmp = topNode;
      topNode = topNode->next;
      delete tmp;
    }
    else
      std::cerr << "Stack empty, cannot pop" << std::endl;
  }

  T top( ) {
    if (!isEmpty( ))
      return topNode->data;
    else
      return nullptr;
  }

  bool isEmpty( ) const { return topNode == nullptr; }
};
