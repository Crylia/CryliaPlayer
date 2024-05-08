#include "Filemonitor.hpp"

Filemonitor::Filemonitor(
  QString path,
  u_long interval,
  const std::function<void(QString, FileEvent)>& cb
) : m_path(path), m_watchInterval(interval) {

  if (!std::filesystem::exists(m_path.toStdString( ))) {
    return;
  }

  this->moveToThread(&m_thread);
  connect(&m_thread, &QThread::finished, this, &QObject::deleteLater);
  connect(this, &Filemonitor::operate, this, [this, cb]( ) {
    start(cb);
    });

  for (auto& file : std::filesystem::recursive_directory_iterator(m_path.toStdString( ))) {
    m_knownFilePaths[QString::fromStdString(file.path( ).string( ))] = std::filesystem::last_write_time(file);
  }

  m_thread.start( );
}

Filemonitor::~Filemonitor( ) {
  m_thread.quit( );
  m_thread.wait( );
}

bool Filemonitor::contains(const QString& key) {
  auto el = m_knownFilePaths.find(key);
  return el != m_knownFilePaths.end( );
}

void Filemonitor::start(const std::function<void(QString, FileEvent)>& cb) {
  while (m_thread.isRunning( )) {
    m_thread.sleep(m_watchInterval);

    auto it = m_knownFilePaths.begin( );
    while (it != m_knownFilePaths.end( )) {
      if (!std::filesystem::exists(it->first.toStdString( )))
        it = m_knownFilePaths.erase(it);
      else
        it++;
    }

    for (auto& file : std::filesystem::recursive_directory_iterator(m_path.toStdString( ))) {
      auto current_file_last_write_time = std::filesystem::last_write_time(file);
      if (!contains(QString::fromStdString(file.path( ).string( )))) {
        m_knownFilePaths[QString::fromStdString(file.path( ).string( ))] = current_file_last_write_time;
        cb(QString::fromStdString(file.path( ).string( )), FileEvent::created);
      } else {
        if (m_knownFilePaths[QString::fromStdString(file.path( ).string( ))] != current_file_last_write_time) {
          m_knownFilePaths[QString::fromStdString(file.path( ).string( ))] = current_file_last_write_time;
          cb(QString::fromStdString(file.path( ).string( )), FileEvent::modified);
        }
      }
    }
  }
}
