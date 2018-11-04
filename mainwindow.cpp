#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "randommoviegenerator.h"
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

    QPixmap img(":/img/logo.png");
    ui->logo->setPixmap(img);
    ui->logo->setScaledContents( true );
    ui->logo->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QPixmap loading(":/img/loading.jpg");
    ui->posterImg->setPixmap(loading);
    ui->posterImg->setScaledContents( true );
    ui->posterImg->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->listWidget->setWordWrap(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest(QString s)
{
    ui->listWidget->clear();
    QEventLoop eventLoop;
    QNetworkAccessManager manager;

    connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req(QUrl("http://www.omdbapi.com/?"+s+"&apikey=29d9fa76"));
    QNetworkReply *reply = manager.get(req);
    eventLoop.exec();
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    if(document.isObject())
    {
        QJsonObject values = document.object();
        foreach( const QString &key, values.keys())
        {
            if(key != "Poster")
            {
                QListWidgetItem *itm = new QListWidgetItem();
                QListWidgetItem *itm2 = new QListWidgetItem();
                QListWidgetItem *space = new QListWidgetItem();
                QJsonValue val = values.value(key);
                itm->setText(key);

                itm2->setText(val.toString());
                ui->listWidget->addItem(itm);
                ui->listWidget->addItem(itm2);
                ui->listWidget->addItem(space);
                qDebug()<< key;
            }

        }
        if(values["Poster"].toString() == "N/A")
        {
            QPixmap noImg(":/img/noPhotoFound.png");
            ui->posterImg->setPixmap(noImg);
        }
        else
        {
            QEventLoop eLoop;
            connect(&manager, SIGNAL(finished(QNetworkReply*)), &eLoop, SLOT(quit()));
            QNetworkRequest request(QUrl(values["Poster"].toString()));
            QNetworkReply *reply = manager.get(request);
            eLoop.exec();

            QByteArray arr = reply->readAll();
            QPixmap img;
            img.loadFromData(arr);
            ui->posterImg->setPixmap(img);
        }
    }
    film.setObj(document.object());
    film.setInfo();
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

    return "t="+ text;
}


void MainWindow::on_searchButton_clicked()
{
    sendRequest(setSearchedFilm(ui->lineEdit->text()));
}

void MainWindow::on_randomMovieButton_clicked()
{
   randomMovieGenerator randomMovie;
   randomMovie.setKeyValue();

   sendRequest("i=" + randomMovie.getKeyValue());


   qDebug() << randomMovie.getKeyValue();
}
