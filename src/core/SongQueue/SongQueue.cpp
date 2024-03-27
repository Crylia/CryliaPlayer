#include "SongQueue.h"

SongQueue::SongQueue( ) {
  queue = new ConditionalCircularLinkedList(false);

  // Its never going to be linked, I'm just too lazy to make a new implementation thats almost the same
  priorityQueue = new ConditionalCircularLinkedList(false);
}

SongQueue::~SongQueue( ) { }

void SongQueue::PopulateQueue(const std::list<Song*>& songList) {
  for (Song* song : songList) {
    queue->Append(song);
  }
}

void SongQueue::Next( ) {
  if (priorityQueue->IsEmpty( )) {
    topSong = queue->GetNext( );
    queue->Advance( );

    return;
  }

  topSong = priorityQueue->GetNext( );
  priorityQueue->Advance( );
}

void SongQueue::JumpToSong(Song* song, bool fromPrioQueue) {
  if (fromPrioQueue) {
    if (priorityQueue->IsEmpty( ))
      return;

    while (priorityQueue->GetNext( ) != song) {
      priorityQueue->Advance( );
      topSong = song;
    }
  }

  if (queue->IsEmpty( ))
    return;

  while (queue->GetNext( ) != song) {
    queue->Advance( );
    topSong = song;
  }
}

void SongQueue::AddToPriorityQueue(Song* song) {
  priorityQueue->Append(song);
}

bool SongQueue::IsEmpty( ) {
  return queue->IsEmpty( ) && priorityQueue->IsEmpty( );
}

Song* SongQueue::Top( ) { return topSong; }

void SongQueue::SetTop(Song* song) { topSong = song; }

void SongQueue::RemoveSongFromPriorityQueue(Song* song) {
  if (priorityQueue->IsEmpty( ))
    return;

  priorityQueue->RemoveSong(song);
}

void SongQueue::MoveSongInPriorityQueue(Song* songToMove, Song* otherSong, bool beforeElseAfter) {
  if (priorityQueue->IsEmpty( ))
    return;

  if (beforeElseAfter)
    priorityQueue->AddSongBefore(songToMove, otherSong);
  else
    priorityQueue->AddSongAfter(songToMove, otherSong);
}

void SongQueue::ShufflePlaylist( ) {
  if (queue && queue->IsEmpty( )) return;
  //First backup the original list state
  queue_original = new ConditionalCircularLinkedList(queue);

  queue->Shuffle( );
}

void SongQueue::RestorePlaylist( ) {
  if (queue_original == nullptr) return;

  queue = new ConditionalCircularLinkedList(queue_original);
}

void SongQueue::LinkQueue(bool link) {
  queue->SetListMode(link);
}
