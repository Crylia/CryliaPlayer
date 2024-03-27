#pragma once

#include <string>

class Song {
private:
  // Song information
  const std::string& title;
  const std::string& album;
  const std::string& artist;
  const std::string& codec;
  const std::string& comment;
  const std::string& copyright;
  const std::string& publisher;
  const std::string& genre;
  const std::string& encoded_by;
  const std::string& date;
  const std::string& language;
  const std::string& albumCoverPath;
  const std::string& path;
  const int& length;

  // Our own Metadata
  bool favorite = false;
  int playCount = 0;
  std::string discovered;

public:
  Song(
    std::string title,
    std::string album,
    std::string artist,
    std::string codec,
    std::string comment,
    std::string copyright,
    std::string publisher,
    std::string genre,
    std::string encoded_by,
    std::string date,
    std::string language,
    std::string albumCoverPath,
    std::string path,
    int length,
    std::string discoveredPath
  );
  ~Song( );

  void SetFavorite(bool fav) { favorite = fav; }

  void IncrementPlayCount( ) { playCount++; }

  std::string GetPath( ) { return path; };

  std::string GetTitle( ) { return title; }
  std::string GetAlbum( ) { return album; }
  std::string GetArtist( ) { return artist; }

};
