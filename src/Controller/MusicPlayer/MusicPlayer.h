#pragma once

#include "../../core/audio/audio.h"
#include "../../core/SongHistory/SongHistory.hpp"
#include "../../core/SongQueue/SongQueue.h"
#include "../../core/song/song.h"

enum Loop {
  None,
  Once,
  All
};

class MusicPlayer {
public:
  static MusicPlayer& getInstance( ) {
    static MusicPlayer instance;
    return instance;
  }

private:
  MusicPlayer( );

  // 0 no shuffle, 1 shuffling
  int shuffle = 0;
  // None, Once, All
  Loop loop = None;
  // 0 stopped, 1 playing
  bool playing = 0;

  // Song queue, will be filled with the entire playlist by default
  SongQueue* songQueue;

  // Contain all played songs
  SongHistory<Song*>* songHistory;

  Audio& audio = Audio::getInstance( );

  void shuffleQueue( );
  void setQueueLoop( );

public:
  ~MusicPlayer( );

  MusicPlayer(MusicPlayer const&) = delete;
  void operator=(MusicPlayer const&) = delete;

  /**
   * @brief Will start playing the given song and put itself at the queue top.
   *
   * @param song Song that will start playing
   */
  void PlaySong(Song* song);

  /**
   * @brief Skip the current song and play the next in queue,
   * if nothing is in queue it will stop playing anything.
   *
   */
  void NextSong( );

  /**
   * @brief Jumps the queue to the given song keeping the non altered queue intact
   *
   * @param song
   * @param isPrioQueue If the song is in the prio queue or normal queue
   */
  void NextSong(Song* song, bool isPrioQueue);

  /**
   * @brief Rewind the currently playing song to the beginning if playtime >= 5 seconds.
   * Otherwise play the top song in the history stack
   *
   */
  void PreviousSong( );

  /**
   * @brief Skip the song to the given timestamp
   *
   * @param skipTo time as positive integer
   */
  void SkipToTimestamp(unsigned const int& skipTo);

  /**
   * @brief Get the current Song progression as an positive integer
   *
   * @return int current timestamp
   */
  int GetSongProgression( );

  /**
   * @brief Get the Currently Playing Song
   *
   * @return Song& Song thats currently playing
   */
  Song* GetCurrentlyPlaying( );

  void SetShuffle(bool shuffle) { this->shuffle = shuffle; }
  void SetLoop(Loop loop) { this->loop = loop; }

  void AddSongToQueue(Song* song);
  void RemoveSongFromQueue(Song* song);
  void MoveSongInQueue(Song* songToMove, Song* otherSong, bool beforeElseAfter);
};
