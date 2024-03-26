#include "MusicPlayer.h"

MusicPlayer::~MusicPlayer( ) { }

void MusicPlayer::PlaySong(Song* song) {
  songHistory->push(songQueue->Top( ));
  songQueue->SetTop(song);

  audio.PlaySong(songQueue->Top( )->GetPath( ));
}

void MusicPlayer::NextSong( ) {
  if (songQueue->IsEmpty( )) {
    audio.StopMusic( );
    return;
  }

  songHistory->push(songQueue->Top( ));
  songQueue->Next( );

  audio.PlaySong(songQueue->Top( )->GetPath( ));
}

void MusicPlayer::NextSong(Song* song, bool isPrioQueue) {
  if (songQueue->IsEmpty( )) {
    audio.StopMusic( );
    return;
  }

  songHistory->push(songQueue->Top( ));
  songQueue->JumpToSong(song, isPrioQueue);

  audio.PlaySong(songQueue->Top( )->GetPath( ));
}

void MusicPlayer::PreviousSong( ) {
  if (songHistory->isEmpty( ))
    return;

  songQueue->SetTop(songHistory->top( ));
  songHistory->pop( );

  audio.PlaySong(songQueue->Top( )->GetPath( ));
}

void MusicPlayer::SkipToTimestamp(unsigned const int& skipTo) {
  if (audio.IsMusicPlaying( ) == 0) return;

  audio.SetMusicPos(skipTo);
}

int MusicPlayer::GetSongProgression( ) {
  return audio.IsMusicPlaying( ) == 1 ? audio.GetMusicPos( ) : 0;
}

Song* MusicPlayer::GetCurrentlyPlaying( ) {
  return songQueue->Top( );
}

//For the PriorityQueue
void MusicPlayer::AddSongToQueue(Song* song) {
  songQueue->AddToPriorityQueue(song);
}

void MusicPlayer::RemoveSongFromQueue(Song* song) {
  songQueue->RemoveSongFromPriorityQueue(song);
}

void MusicPlayer::MoveSongInQueue(Song* songToMove, Song* otherSong, bool beforeElseAfter) {
  songQueue->MoveSongInPriorityQueue(songToMove, otherSong, beforeElseAfter);
}

void MusicPlayer::shuffleQueue( ) {
  shuffle ? songQueue->ShufflePlaylist( ) : songQueue->RestorePlaylist( );
}

void MusicPlayer::setQueueLoop( ) {
  loop == All ? songQueue->LinkQueue(true) : songQueue->LinkQueue(false);
}
