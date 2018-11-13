#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

class dbManager
{
private:
    QSqlDatabase db;

public:
    void initialiseDB();
    void createAccount(QString,QString, QString);


};

#endif // DBMANAGER_H
