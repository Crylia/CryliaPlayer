#pragma once

#include <iostream>
#include <QString>
#include <QThread>
#include <chrono>
#include <unordered_map>
#include <string>
#include <filesystem>

enum class FileEvent { created, modified, erased };

class Filemonitor : public QObject {
  Q_OBJECT
private:
  QString m_path;
  u_long m_watchInterval;
  std::unordered_map<QString, std::filesystem::file_time_type> m_knownFilePaths;

  bool contains(const QString& key);

  QThread m_thread;
public:
  Filemonitor(QString path, u_long interval, const std::function<void(QString, FileEvent)>& cb);
  ~Filemonitor( );

public slots:
  void start(const std::function<void(QString, FileEvent)>& cb);

signals:
  void operate( );
};

