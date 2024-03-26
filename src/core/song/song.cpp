#include "song.h"

Song::Song(
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
) : title(title),
album(album),
artist(artist),
codec(codec),
comment(comment),
copyright(copyright),
publisher(publisher),
genre(genre),
encoded_by(encoded_by),
date(date),
language(language),
albumCoverPath(albumCoverPath),
path(path),
length(length) {

}

Song::~Song( ) { }
