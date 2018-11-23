#ifndef RANDOMMOVIEGENERATOR_H
#define RANDOMMOVIEGENERATOR_H
#include <QtGui>
#include <QtCore>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class randomMovieGenerator
{
private:
    QVector<QString> prefix = {"tt","nm","co","ev","ni"};
    QString randomNum;
    QString keyValue;
public:

    int generateRandomNum();
    QString getPrefix();
    void setKeyValue();
    QString getKeyValue();
};

#endif // RANDOMMOVIEGENERATOR_H
