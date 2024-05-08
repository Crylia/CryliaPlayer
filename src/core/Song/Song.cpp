#include "Song.hpp"

Song::Song(QString title, QString album, QString artist, QString codec,
           QString comment, QString copyright, QString publisher, QString genre,
           QString encoded_by, QString date, QString language,
           QString albumCoverPath, QString path, int length)
    : m_title(title), m_album(album), m_artist(artist), m_codec(codec),
      m_comment(comment), m_copyright(copyright), m_publisher(publisher),
      m_genre(genre), m_encoded_by(encoded_by), m_date(date),
      m_language(language), m_albumCoverPath(albumCoverPath), m_path(path),
      m_length(length) {}
