#pragma once

#include <QObject>
#include <QString>

class Song : public QObject {
  Q_OBJECT

    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString album READ album)
    Q_PROPERTY(QString artist READ artist)
    Q_PROPERTY(QString codec READ codec)
    Q_PROPERTY(QString comment READ comment)
    Q_PROPERTY(QString copyright READ copyright)
    Q_PROPERTY(QString publisher READ publisher)
    Q_PROPERTY(QString genre READ genre)
    Q_PROPERTY(QString encoded_by READ encoded_by)
    Q_PROPERTY(QString date READ date)
    Q_PROPERTY(QString language READ album)
    Q_PROPERTY(QString albumCoverPath READ albumCoverPath)
    Q_PROPERTY(QString path READ path)
    Q_PROPERTY(int length READ length)

    Q_PROPERTY(
      bool favorite READ favorite WRITE setFavorite NOTIFY favoriteChanged)
    Q_PROPERTY(int playCount READ playCount NOTIFY
      playCountChanged)

private:
  // Song information
  const QString m_title;
  const QString m_album;
  const QString m_artist;
  const QString m_codec;
  const QString m_comment;
  const QString m_copyright;
  const QString m_publisher;
  const QString m_genre;
  const QString m_encoded_by;
  const QString m_date;
  const QString m_language;
  const QString m_albumCoverPath;
  const QString m_path;
  const int m_length;

  // Our own Metadata
  bool m_favorite = false;
  int m_playCount = 0;

public:
  Song(QString title, QString album, QString artist, QString codec,
    QString comment, QString copyright, QString publisher, QString genre,
    QString encoded_by, QString date, QString language,
    QString albumCoverPath, QString path, int length);

  void setFavorite(bool fav) {
    if (m_favorite == fav)
      return;
    m_favorite = fav;
    emit favoriteChanged( );
  }
  void incrementPlayCount( ) { m_playCount++; }

  QString title( ) const { return m_title; }
  QString album( ) const { return m_album; }
  QString artist( ) const { return m_artist; }
  QString codec( ) const { return m_codec; }
  QString comment( ) const { return m_comment; }
  QString copyright( ) const { return m_copyright; }
  QString publisher( ) const { return m_publisher; }
  QString genre( ) const { return m_genre; }
  QString encoded_by( ) const { return m_encoded_by; }
  QString date( ) const { return m_date; }
  QString language( ) const { return m_language; }
  QString albumCoverPath( ) const { return m_albumCoverPath; }
  QString path( ) const { return m_path; }
  int length( ) const { return m_length; }

  bool favorite( ) const { return m_favorite; }
  int playCount( ) const { return m_playCount; }

signals:
  void favoriteChanged( );
  void playCountChanged( );
};
