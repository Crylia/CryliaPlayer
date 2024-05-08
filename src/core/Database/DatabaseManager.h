#pragma once

#include <QSqlDatabase>
#include <QString>
#include <iostream>

class DbManager {
private:
  QSqlDatabase m_db;
public:
  DbManager( );
  ~DbManager( );
};

