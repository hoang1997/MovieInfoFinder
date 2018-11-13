#include "dbmanager.h"
#include <QDebug>


void dbManager::initialiseDB()
{
    const QString DRIVER("QSQLITE");
    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        db =QSqlDatabase::addDatabase(DRIVER);
    }
    db.setDatabaseName("userDatabase.db");
    if(!db.open())
    {
        qDebug()<<db.lastError();
    } else {qDebug()<< "Database Open";}
}

void dbManager::createAccount(QString email, QString userName, QString password)
{



}






