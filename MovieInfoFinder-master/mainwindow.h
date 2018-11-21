#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "movie.h"
#include "wishlist.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void sendRequest(QString);
    void setMovie(const QJsonObject);
    void setMovieInfo(QJsonObject);
    void setMoviePoster(QString);
    QString setSearchedFilm(QString);

    QString getRequestUrl(QString);


private slots:
    void on_searchButton_clicked();

    void on_randomMovieButton_clicked();




    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString searchedFilm;
    movie film;
    wishList *wl;









};

#endif // MAINWINDOW_H
