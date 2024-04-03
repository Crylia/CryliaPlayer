#include "DatabaseManager.h"

DbManager::DbManager( ) :
  m_db(QSqlDatabase::addDatabase("QSQLITE")) {
  m_db.setDatabaseName(QString("../../../database/CryliaPlayerDB.sqlite3"));

  if (!m_db.open( )) {
    std::cout << "Error: Could not open database" << std::endl;
  }

}

DbManager::~DbManager( ) { }
