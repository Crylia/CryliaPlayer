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

class Audio {
public:
  static Audio& getInstance(const std::string path) {
    static Audio instance(path);
    return instance;
  }
private:
  Audio(const std::string path);

  const std::string path;
  const std::string artist;
  const std::string album;

  Mix_Music* music;

public:
  ~Audio( );

  Audio(Audio const&) = delete;
  void operator=(Audio const&) = delete;

  std::string GetTitle( );
  std::string GetArtist( );
  std::string GetAlbum( );

  int GetMusicPos( );
  int GetMusicDuration( );
  int SetMusicPos(int pos);

  QPixmap GetAlbumCover( );

  void StartMusic( );
  void PauseMusic( );
  void ResumeMusic( );
  bool IsMusicPlaying( );

  void SetVolume(int vol);
  int GetVolume( );
};
