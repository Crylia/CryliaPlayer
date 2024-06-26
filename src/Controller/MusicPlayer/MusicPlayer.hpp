#pragma once

#include <QObject>
#include <QPixmap>

#include "../../core/Audio/Audio.hpp"
#include "../../core/CliArgHandler/CliArgHandler.hpp"
#include "../../core/Song/Song.hpp"
#include "../../core/SongHistory/SongHistory.hpp"
#include "../../core/SongQueue/SongQueue.hpp"

class MusicPlayer : public QObject {
  Q_OBJECT
public:
  static MusicPlayer &getInstance() {
    static MusicPlayer instance;
    return instance;
  }

private:
  MusicPlayer();

  // 0 no shuffle, 1 shuffling
  int shuffle = 0;
  // None, Once, All
  Loop loop = Loop::None;
  // 0 stopped, 1 playing
  bool playing = 0;

  // Song queue, will be filled with the entire playlist by default
  SongQueue *songQueue;

  // Contain all played songs
  SongHistory<Song *> *songHistory;

  Audio &audio = Audio::getInstance();

  void shuffleHandler();
  void setQueueLoop();

public:
  ~MusicPlayer() = default;

  MusicPlayer(MusicPlayer const &) = delete;
  void operator=(MusicPlayer const &) = delete;

  /**
   * @brief Will start playing the given song and put itself at the queue top.
   *
   * @param song Song that will start playing
   */
  void PlaySong(std::unique_ptr<Song> song);

  /**
   * @brief Skip the current song and play the next in queue,
   * if nothing is in queue it will stop playing anything.
   *
   */
  void NextSong();

  /**
   * @brief Jumps the queue to the given song keeping the non altered queue
   * intact
   *
   * @param song
   * @param isPrioQueue If the song is in the prio queue or normal queue
   */
  void NextSong(std::unique_ptr<Song> song, bool isPrioQueue);

  /**
   * @brief Rewind the currently playing song to the beginning if playtime >= 5
   * seconds. Otherwise play the top song in the history stack
   *
   */
  void PreviousSong();

  /**
   * @brief Skip the song to the given timestamp
   *
   * @param skipTo time as positive integer
   */
  void SkipToTimestamp(unsigned const int &skipTo);

  /**
   * @brief Get the current Song progression as an positive integer
   *
   * @return int current timestamp
   */
  int GetSongProgression();

  /**
   * @brief Get the Currently Playing Song
   *
   * @return Song& Song thats currently playing
   */
  std::unique_ptr<Song> GetCurrentlyPlaying();

  /**
   * @brief Will either play or pause a current song, if not song is active it
   * returns false.
   *
   * @return true if currently playing
   * @return false if paused or nothing playing
   */
  bool PlayPause();

  bool IsPlaying();

  QPixmap GetAlbumArt();

  void SetShuffle(bool shuffle) {
    this->shuffle = shuffle;
    shuffleHandler();
  }
  bool IsActive();
  bool GetShuffle() { return shuffle; }
  void SetLoop(Loop loop) { this->loop = loop; }
  Loop GetLoop() { return loop; }
  u_short GetVolume() { return audio.GetVolume(); }
  void SetVolume(u_short volume) { audio.SetVolume(volume); }
  int GetSongDuration() { return audio.GetMusicDuration(); }

  void AddSongToQueue(std::unique_ptr<Song> song);
  void RemoveSongFromQueue(std::unique_ptr<Song> song);
  void MoveSongInQueue(std::unique_ptr<Song> songToMove,
                       std::unique_ptr<Song> otherSong, bool beforeElseAfter);

signals:
  void SongChanged();
};
