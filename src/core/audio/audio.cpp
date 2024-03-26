#include "audio.h"

Audio::Audio( ) {
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    std::cerr << "SDL initialization failed: " << SDL_GetError( ) << std::endl;
    return;
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) == -1) {
    std::cerr << "SDL_mixer initialization failed: " << Mix_GetError( ) << std::endl;
    SDL_Quit( );
    return;
  }
};

Audio::~Audio( ) {
  Mix_FreeMusic(music);
  Mix_CloseAudio( );
  SDL_Quit( );
}

void Audio::StartMusic( ) {
  if (Mix_PlayingMusic( ) == 0) {
    //TODO: Get the loop status from the FloatingControls widget and replace the 1
    Mix_PlayMusic(music, 1);
  }
}

void Audio::StopMusic( ) {
  Mix_HaltMusic( );
}

void Audio::PlaySong(const std::string path) {
  if (music)
    Mix_FreeMusic(music);

  this->path = path;

  music = Mix_LoadMUS(path.c_str( ));
  if (!music) {
    std::cerr << "Failed to load MP3 file: " << Mix_GetError( ) << std::endl;
    Mix_CloseAudio( );
    SDL_Quit( );
    return;
  }
}

void Audio::PauseMusic( ) {
  if (Mix_PlayingMusic( ) == 1) {
    Mix_PauseMusic( );
  }
}

void Audio::ResumeMusic( ) {
  if (Mix_PausedMusic( ) == 1) {
    Mix_ResumeMusic( );
  }
}

bool Audio::IsMusicPlaying( ) {
  return (Mix_PlayingMusic( ) != 0);
}

std::string Audio::GetTitle( ) {
  std::cout << Mix_GetMusicTitleTag(music) << std::endl;
  return Mix_GetMusicTitleTag(music);
}

std::string Audio::GetArtist( ) {
  return Mix_GetMusicArtistTag(music);
}

int Audio::GetMusicPos( ) {
  return Mix_GetMusicPosition(music);
}

int Audio::SetMusicPos(int pos) {
  return Mix_SetMusicPosition(pos);
}

int Audio::GetMusicDuration( ) {
  return Mix_MusicDuration(music);
}

QPixmap Audio::GetAlbumCover( ) {
  AVFormatContext* fc = avformat_alloc_context( );
  if (avformat_open_input(&fc, this->path.c_str( ), NULL, NULL) != 0) {
    SDL_Log("Error opening audio file");
    return QPixmap( );
  }

  if (avformat_find_stream_info(fc, NULL) < 0) {
    SDL_Log("Could not find stream information");
    return QPixmap( );
  }

  AVPacket packet;
  int ret;

  while ((ret = av_read_frame(fc, &packet)) >= 0) {
    AVStream* stream = fc->streams[packet.stream_index];
    if (stream->disposition & AV_DISPOSITION_ATTACHED_PIC) {
      return QPixmap::fromImage(QImage::fromData(reinterpret_cast<const uchar*>(packet.data), packet.size));
    }
    av_packet_unref(&packet);
  }

  avformat_close_input(&fc);
  avformat_free_context(fc);

  return QPixmap( );
}

int Audio::GetVolume( ) {
  return Mix_GetMusicVolume(music);
}

void Audio::SetVolume(int vol) {
  if (vol > MIX_MAX_VOLUME)
    vol = MIX_MAX_VOLUME;
  Mix_VolumeMusic(vol);
}
