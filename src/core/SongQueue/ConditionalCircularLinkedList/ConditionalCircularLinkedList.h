#pragma once

#include <iostream>

#include "../../song/song.h"

class ConditionalCircularLinkedList {
private:

  struct Node {
    Node* next;
    Song* data;

    Node(Song* song) : data(song), next(nullptr) { }
  };

  Node* head;

  // Variable to keep the current position that we seek
  Node* current;

  // Variable to either link or unlink the list
  bool isLinked;
public:
  ConditionalCircularLinkedList( );
  ConditionalCircularLinkedList(bool isLinked) : head(nullptr), isLinked(isLinked) { }

  /**
   * @brief Append a new song to the queue
   *
   * @param song
   */
  void Append(Song* song);

  /**
   * @brief Clear the entire list so its brand spanking new.
   *
   */
  void Clear( );

  /**
   * @brief Depending on if the queue is supposed to be looping, this will link
   * up the end of the list, with its beginning to its a circular list.
   * If its not supposed to loop then we break the link and it will be a normal list.
   * @param isLooping Will set the list to circular or normal mode
   */
  void SetListMode(bool isLooping);

  /**
   * @brief Advance the circular list by one, this means setting the "current" pointer
   * to the next element
   *
   */
  void Advance( );

  /**
   * @brief Get the "current" pointer's data
   *
   * @return Song*
   */
  Song* GetNext( );

  void AddSongBefore(Song* newSong, Song* addSongBefore);

  void AddSongAfter(Song* newSong, Song* addSongAfter);

  Song* RemoveSong(Song* removeSong);

  bool IsEmpty( );

  void Shuffle( );
};
