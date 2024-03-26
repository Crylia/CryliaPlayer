#pragma once

#include <iostream>
#include <list>

#include "../song/song.h"
#include "ConditionalCircularLinkedList/ConditionalCircularLinkedList.h"

class SongQueue {
private:

  // The currently playing song
  Song* topSong;

  //Regular song queue, can be unlinked for non looping playlists
  ConditionalCircularLinkedList* queue;
  //Copy of queue to faster restore when unshuffling
  ConditionalCircularLinkedList* queue_original;

  //The name is confusing, but its because the queue itself has priority over the normal one  
  ConditionalCircularLinkedList* priorityQueue;

  void setQueue( );
public:
  SongQueue( );
  ~SongQueue( );

  void PopulateQueue(const std::list<Song*>& songlist);

  /**
   * @brief Will put the next song from the correct sublist as the topSong.
   * This will also remove the song from the queue as its not needed anymore.
   *
   */
  void Next( );

  /**
   * @brief Will put the given song from the priority or normal queue as the top song and remove it
   * from the list
   *
   * @param song
   */
  void JumpToSong(Song* song, bool fromPrioQueue);

  void AddToPriorityQueue(Song* song);

  bool IsEmpty( );

  Song* Top( );

  void SetTop(Song* song);

  void RemoveSongFromPriorityQueue(Song* song);

  void MoveSongInPriorityQueue(Song* songToMove, Song* otherSong, bool beforeElseAfter);

  void ShufflePlaylist( );
  void RestorePlaylist( );

  void LinkQueue(bool link);
};
