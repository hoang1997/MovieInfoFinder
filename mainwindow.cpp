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
#include <QMessageBox>


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

    QStringList chosenDB = (QStringList()<<"OMDB"<<"TMDB");
    ui->comboBox->addItems(chosenDB);
    //Initialises and creates SQLITE3 database named Database
    const QString DRIVER("QSQLITE");
    db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName("Database.db");

    //confirms database connection is established
    if (!db.open())
       {
          qDebug() << "Error: connection with database fail";
       }
       else
       {
          qDebug() << "Database: connection ok";
          QSqlQuery query(db);
          //creates wishlist table
          query.exec("DELETE FROM Wishlist;");

       }
    QSqlQuery query(db);
    //creates wishlist table
    query.exec("CREATE TABLE Wishlist(FilmID string, Title string, Username string, Comments string)");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest(QString s)
{
    qDebug()<<s;
    //clear widget per search
    ui->listWidget->clear();
    //event loop object
    QEventLoop eventLoop;
    //network manager to send and get replies
    QNetworkAccessManager manager;
    //connect and event loop
    connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    //request querying omdb api search
    QUrl p = QUrl(s);
    QNetworkRequest req(p);
    //getting a reply from manager based on the request
    QNetworkReply *reply = manager.get(req);
    eventLoop.exec();
    //convert the reply to a Qjson object
    QJsonObject values = QJsonDocument::fromJson(reply->readAll()).object();

    if(ui->comboBox->currentText() == "OMDB")
    {
        //iterating each key from the qjson object
      setMovieInfo(values);
    }
    else if(ui->comboBox->currentText() == "TMDB")
    {
        QJsonArray r = values["results"].toArray();

        for(int i = 0; i < r.size(); i++)
        {
            QJsonValue val = r[i];
            QJsonObject movieObj = val.toObject();
            setMovieInfo(movieObj);
        }
    }
    film.setObj(values);
    film.setInfo();
}

void MainWindow::setMovieInfo(QJsonObject movieObj)
{

    foreach(const QString &key, movieObj.keys())
    {
        if(key != "Poster" && key != "poster_path")
        {
            //creating items for the list
            QListWidgetItem *itm = new QListWidgetItem();
            QListWidgetItem *itm2 = new QListWidgetItem();
            QListWidgetItem *space = new QListWidgetItem();
            //creating a val
            QJsonValue val = movieObj.value(key);
            itm->setText(key);

            itm2->setText(val.toString());
            ui->listWidget->addItem(itm);
            ui->listWidget->addItem(itm2);
            ui->listWidget->addItem(space);
            qDebug()<< key;
        }
        if(key == "poster_path")
        {
            setMoviePoster( "https://image.tmdb.org/t/p/w500"+movieObj.value(key).toString());
            posterPath = "https://image.tmdb.org/t/p/w500"+movieObj.value(key).toString();
        }
        if(key == "Poster")
        {
            setMoviePoster(movieObj.value(key).toString());
            posterPath = movieObj.value(key).toString();
        }
        if(key == "imdbID")
        {
            id = movieObj.value(key).toString();
        }
        if(key == "Title")
        {
            mTitle = movieObj.value(key).toString();
        }
    }
}

void MainWindow::setMoviePoster(QString link)
{
    qDebug()<<link;
    QNetworkAccessManager manager;
    QEventLoop eLoop;
    connect(&manager, SIGNAL(finished(QNetworkReply*)), &eLoop, SLOT(quit()));
    QUrl u;
    u = QUrl(link);
    QNetworkRequest request(u);
    QNetworkReply *reply = manager.get(request);
    eLoop.exec();
    QByteArray arr = reply->readAll();
    QPixmap img;
    img.loadFromData(arr);
    ui->posterImg->setPixmap(img);

    if(link == "N/A" || link == "null")
    {
        QPixmap noImg(":/img/noPhotoFound.png");
        ui->posterImg->setPixmap(noImg);
    }
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
    return "t=" + text;
}

QString MainWindow::getRequestUrl(QString searchedFilm)
{
    if(ui->comboBox->currentText() == "OMDB")
    {
        if(ui->lineEdit_2->text() != "OMDB API Key")
        {
            return("http://www.omdbapi.com/?"+searchedFilm+ui->lineEdit_2->text());
        }
        else{return("http://www.omdbapi.com/?"+searchedFilm+"&apikey=29d9fa76");}
    }
    else if(ui->comboBox->currentText() == "TMDB")
    {
        if(ui->lineEdit_3->text()!="TMDB API Key")
        {
            return("https://api.themoviedb.org/3/search/movie?api_key="+ui->lineEdit_3->text()+"&query="+searchedFilm);
        }
        return("https://api.themoviedb.org/3/search/movie?api_key=21ffe74ffd34e579e80bb4096979450d&query="+searchedFilm);
    }
    else {
        return(0);
    }
}

void MainWindow::on_searchButton_clicked()
{
    sendRequest(getRequestUrl(setSearchedFilm(ui->lineEdit->text())));
}

void MainWindow::on_randomMovieButton_clicked()
{
   randomMovieGenerator randomMovie;
   randomMovie.setKeyValue();

   sendRequest(getRequestUrl("i=" + randomMovie.getKeyValue()));
   //qDebug() << randomMovie.getKeyValue();
}

void MainWindow::on_pushButton_clicked()
{
    wl = new wishList();
    wl->setModal(true);
    wl->show();
}

//code for adding a film to a wishlist
void MainWindow::on_addToWIshlistButton_clicked()
{
   //creates a query using the open database

   const QString username = "test";
   QSqlQuery query(db);

   //prepares INSERT statements
   query.prepare("INSERT INTO Wishlist(FilmID, Title, Username, Comments) VALUES (:id, :title, :user, :comments)");
   //Binds the appropriate values to the statement to avoid SQL Injection
   query.bindValue(":id", id);
   query.bindValue(":title",mTitle);
   query.bindValue(":user", posterPath);
   query.bindValue(":comments", "No Comments");


   //Confirms the query executes
   if(query.exec())
   {
       qDebug() << "Successfully added to wishlist";
       QMessageBox::StandardButton error;

       error = QMessageBox::information(this,"ERROR:", "Added To Wishlist!");
   }
   else
   {
       qDebug() << query.lastError();
   }
}
