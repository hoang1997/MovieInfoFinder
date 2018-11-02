#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "movie.h"
#include <QGraphicsScene>

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
    void setImage(QString);


private slots:
    void on_searchButton_clicked();



private:
    Ui::MainWindow *ui;
    QString searchedFilm;
    movie film;

    QGraphicsScene *scene;



};

#endif // MAINWINDOW_H
