#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "movie.h"

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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void sendRequest();
    void setMovie(const QJsonObject);
    QString setSearchedFilm(QString);



private slots:
    void on_searchButton_clicked();



private:
    Ui::MainWindow *ui;
    QString searchedFilm;
    movie film;





};

#endif // MAINWINDOW_H
