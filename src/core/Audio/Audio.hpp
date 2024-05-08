#pragma once

extern "C" {
#include <libavformat/avformat.h>
}
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <QImage>
#include <QPixmap>
#include <string>

#include <iostream>

enum class Loop { None, All, Once };

class Audio {
public:
  static Audio& getInstance( ) {
    static Audio instance;
    return instance;
  }
private:
  Audio( );

  QString path;
  QString artist;
  QString album;
  Loop loop;

  Mix_Music* music;

public:
  ~Audio( );

  Audio(Audio const&) = delete;
  void operator=(Audio const&) = delete;

  QString GetTitle( );
  QString GetArtist( );
  QString GetAlbum( );

  int GetMusicPos( );
  int GetMusicDuration( );
  int SetMusicPos(int pos);

  QPixmap GetAlbumCover( );

  void PlaySong(const QString path);

  void StopMusic( );
  void StartMusic( );
  void PauseMusic( );
  void ResumeMusic( );
  bool IsMusicPlaying( );
  void TogglePlayPause( );
  bool IsMusicPaused( );
  void SetVolume(int vol);
  int GetVolume( );
};
