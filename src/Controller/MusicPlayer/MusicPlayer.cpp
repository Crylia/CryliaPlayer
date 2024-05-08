#include "MusicPlayer.hpp"
#include <memory>

MusicPlayer::MusicPlayer()
    : songQueue(new SongQueue()), songHistory(new SongHistory<Song *>()) {
  // TODO: Replace later with automatic song extraction
  auto argsSong{std::make_unique<Song>(
      QString("REPLACE ME"), QString("REPLACE ME"), QString("REPLACE ME"),
      QString(""), QString(""), QString(""), QString(""), QString(""),
      QString(""), QString(""), QString(""), QString(""),
      CliArgHandler::getInstance().getInputFile(), 0)};

  if (argsSong->path() != "") {
    PlaySong(std::move(argsSong));
  }
}

void MusicPlayer::PlaySong(std::unique_ptr<Song> song) {
  songQueue->SetTop(song.get());
  songHistory->push(songQueue->Top());

  audio.PlaySong(songQueue->Top()->path());

  emit SongChanged();
}

void MusicPlayer::NextSong() {
  if (songQueue->IsEmpty()) {
    audio.StopMusic();
    return;
  }

  songHistory->push(songQueue->Top());
  songQueue->Next();

  audio.PlaySong(songQueue->Top()->path());
  emit SongChanged();
}

void MusicPlayer::NextSong(std::unique_ptr<Song> song, bool isPrioQueue) {
  if (songQueue->IsEmpty()) {
    audio.StopMusic();
    return;
  }

  songHistory->push(songQueue->Top());
  songQueue->JumpToSong(song.get(), isPrioQueue);

  audio.PlaySong(songQueue->Top()->path());
  emit SongChanged();
}

void MusicPlayer::PreviousSong() {
  if (songHistory->isEmpty())
    return;

  songQueue->SetTop(songHistory->top());
  songHistory->pop();

  audio.PlaySong(songQueue->Top()->path());
  emit SongChanged();
}

void MusicPlayer::SkipToTimestamp(unsigned const int &skipTo) {
  if (audio.IsMusicPlaying() == 0)
    return;

  audio.SetMusicPos(skipTo);
}

int MusicPlayer::GetSongProgression() {
  return audio.IsMusicPlaying() == 1 ? audio.GetMusicPos() : 0;
}

std::unique_ptr<Song> MusicPlayer::GetCurrentlyPlaying() {
  return std::unique_ptr<Song>(songQueue->Top());
}

// For the PriorityQueue
void MusicPlayer::AddSongToQueue(std::unique_ptr<Song> song) {
  songQueue->AddToPriorityQueue(song.get());
}

void MusicPlayer::RemoveSongFromQueue(std::unique_ptr<Song> song) {
  songQueue->RemoveSongFromPriorityQueue(song.get());
}

void MusicPlayer::MoveSongInQueue(std::unique_ptr<Song> songToMove,
                                  std::unique_ptr<Song> otherSong,
                                  bool beforeElseAfter) {
  songQueue->MoveSongInPriorityQueue(songToMove.get(), otherSong.get(),
                                     beforeElseAfter);
}

void MusicPlayer::shuffleHandler() {
  shuffle ? songQueue->ShufflePlaylist() : songQueue->RestorePlaylist();
}

void MusicPlayer::setQueueLoop() {
  loop == Loop::All ? songQueue->LinkQueue(true) : songQueue->LinkQueue(false);
}

bool MusicPlayer::IsPlaying() { return audio.IsMusicPaused(); }

bool MusicPlayer::IsActive() { return audio.IsMusicPlaying(); }

QPixmap MusicPlayer::GetAlbumArt() { return audio.GetAlbumCover(); }

/**
 * @brief Resumes or Plays the music depending on the current state, if no music
 * is playing it returns false
 *
 * @return true Music is Playing
 * @return false Music is Paused or nothing is playing
 */
bool MusicPlayer::PlayPause() {
  if (!audio.IsMusicPlaying())
    return false;

  audio.TogglePlayPause();

  emit SongChanged();
  return !audio.IsMusicPaused();
}
