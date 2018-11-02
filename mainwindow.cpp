#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtCore>
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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest()
{
    ui->listWidget->clear();
    QEventLoop eventLoop;
    QNetworkAccessManager manager;

    connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req(QUrl("http://www.omdbapi.com/?t="+setSearchedFilm(ui->lineEdit->text())+"&apikey=29d9fa76"));
    QNetworkReply *reply = manager.get(req);
    eventLoop.exec();
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    //QListWidgetItem *item = new QListWidgetItem();

    if(document.isObject())
    {
        QJsonObject values = document.object();
        //item->setText(values["Title"].toString());
        //ui->listWidget->addItem(item);
        foreach( const QString &key, values.keys())
        {
            int i = 0;
            QListWidgetItem *itm = new QListWidgetItem();
            QListWidgetItem *itm2 = new QListWidgetItem();
            QJsonValue val = values.value(key);
            itm->setText(key);
            itm2->setText(val.toString());
            ui->listWidget->addItem(itm);
            ui->listWidget->addItem(itm2);
            i++;
        }

    }

    film.setObj(document.object());
    film.setInfo();
    setImage(film.poster);
}

QString MainWindow::setSearchedFilm(QString text)
{
    for(int i = 0; i < text.length(); ++i)
    {
       if(text[i] == " ")
       {
           text[i] = '+';
       }
    }
    return text;
}

void MainWindow::setImage(QString url)
{


        QImage image(url);
        QImage img = image.scaled(800,600,Qt::KeepAspectRatio);


        QGraphicsPixmapItem *itm = new QGraphicsPixmapItem(QPixmap::fromImage(img));

        scene->addItem(itm);

}



void MainWindow::on_searchButton_clicked()
{
    sendRequest();
}
