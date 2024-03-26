#include "ConditionalCircularLinkedList.h"

ConditionalCircularLinkedList::ConditionalCircularLinkedList( ) { }

void ConditionalCircularLinkedList::Append(Song* song) {
  Node* newNode = new Node(song);
  if (head == nullptr) {
    head = newNode;

    // Only link back when its supposed to
    if (isLinked)
      head->next = head;

    current = head;
  }
  else {
    Node* tmp = head;

    while (tmp->next != head)
      tmp = tmp->next;

    tmp->next = newNode;

    // Again make sure to only link when supposed to
    if (isLinked)
      newNode->next = head;
  }
}

void ConditionalCircularLinkedList::SetListMode(bool isLooping) {
  if (head == nullptr) {
    std::cout << "WARN: List is empty, cannot set mode" << std::endl;
    return;
  }

  Node* tmp = head;
  while (tmp->next != head)
    tmp = tmp->next;

  if (!isLooping)
    tmp->next = nullptr;
  else
    tmp->next = head;
}

void ConditionalCircularLinkedList::Clear( ) {
  while (head != nullptr) {
    Node* tmp = head;
    head = head->next;
    delete tmp;
    delete current;
  }
}

void ConditionalCircularLinkedList::Advance( ) {
  if (current != nullptr)
    current = current->next;
}

Song* ConditionalCircularLinkedList::GetNext( ) {
  if (current != nullptr)
    return current->data;
}

void ConditionalCircularLinkedList::AddSongBefore(Song* newSong, Song* addSongBefore) {
  if (head == nullptr) return;

  Node* newNode = new Node(newSong);

  Node* current = head;
  Node* prev = nullptr;

  do {
    if (current->data == addSongBefore) {
      if (prev == nullptr) {
        newNode->next = head;
        head = newNode;

        Node* lastNode = head;
        while (lastNode->next != head)
          lastNode = lastNode->next;

        if (isLinked)
          lastNode->next = head;
      }
      else {
        prev->next = newNode;
        newNode->next = current;
      }
      return;
    }
    prev = current;
    current = current->next;

  } while (current != head);
}

void ConditionalCircularLinkedList::AddSongAfter(Song* newSong, Song* addSongAfter) {
  if (head == nullptr) return;

  Node* newNode = new Node(newSong);

  Node* current = head;

  do {
    if (current->data == addSongAfter) {
      newNode->next = current->next;
      current->next = newNode;
      return;
    }
    current = current->next;
  } while (current != head);

}

Song* ConditionalCircularLinkedList::RemoveSong(Song* removeSong) {
  if (head == nullptr) return nullptr;

  Node* current = head;
  Node* prev = nullptr;

  do {
    if (current->data == removeSong) {
      if (prev == nullptr) {
        head = current->next;
        Node* lastNode = head;
        while (lastNode->next != current)
          lastNode = lastNode->next;

        if (isLinked)
          lastNode->next = head;

        Song* deletedSong = current->data;
        delete current;
        return deletedSong;
      }
      else {
        prev->next = current->next;

        Song* deletedSong = current->data;
        delete current;
        return deletedSong;
      }
    }
    prev = current;
    current = current->next;
  } while (current != head);
}

bool ConditionalCircularLinkedList::IsEmpty( ) {
  return current == nullptr;
}

void ConditionalCircularLinkedList::Shuffle( ) {
  int cnt = 0;
  Node* tmp = head;

  while (tmp != nullptr) {
    cnt++;
    tmp = tmp->next;
  }

  Node** nodes = new Node * [cnt];

  tmp = head;
  for (int i = 0; i < cnt; i++) {
    nodes[i] = tmp;
    tmp = tmp->next;
  }

  for (int i = cnt; i > 0; i--) {
    int j = rand( ) % (i + 1);

    Node* tmp = nodes[i];
    nodes[i] = nodes[j];
    nodes[j] = tmp;
  }

  head = nodes[0];
  for (int i = 0; i < cnt - 1; i++)
    nodes[i]->next = nodes[i + 1];

  nodes[cnt - 1]->next = nullptr;

  delete[] nodes;
}
