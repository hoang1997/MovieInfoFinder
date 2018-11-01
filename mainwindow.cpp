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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest()
{
    QEventLoop eventLoop;
    QNetworkAccessManager manager;

    connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req(QUrl("http://www.omdbapi.com/?t="+ui->lineEdit->text()+"&apikey=29d9fa76"));
    QNetworkReply *reply = manager.get(req);
    eventLoop.exec();
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    if(document.isObject())
    {
        QJsonObject values = document.object();

        for(auto key: values.keys())
        {
             qDebug()<<key<<" : "<<values[key].toString();
        }
    }
}

void MainWindow::on_searchButton_clicked()
{
    sendRequest();
}
