#include "wishlist.h"
#include "ui_wishlist.h"

wishList::wishList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wishList)
{
    ui->setupUi(this);
    getMovieTitles();

}

wishList::~wishList()
{
    delete ui;
}

void wishList::getMovieTitles()
{
    ui->comboBox->clear();
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
       }

    QSqlQuery query;
    query.exec("SELECT * FROM Wishlist");

    while (query.next())
    {
        QString imdbID = query.value(0).toString();
        QString film = query.value(1).toString();
        QString comment = query.value(3).toString();
        posterPath = query.value(4).toString();
        setWishListMovie(film,comment);
    }
}

void wishList::setWishListMovie(QString title, QString com)
{

     ui->comboBox->addItem(title);
     QTreeWidgetItem *movie = new QTreeWidgetItem(ui->treeWidget);
     QTreeWidgetItem *comment = new QTreeWidgetItem(movie);
     ui->treeWidget->addTopLevelItem(movie);
     movie->setText(0, title);
     comment->setText(0,com);
}

void wishList::on_pushButton_clicked()
{
    QSqlQuery query(db);

    query.prepare("UPDATE Wishlist SET Comments = (:comments) WHERE Title = (:title)");
    //Binds the appropriate values to the statement to avoid SQL Injection

    query.bindValue(":title", ui->comboBox->currentText());
    query.bindValue(":comments", ui->lineEdit->text());

    //Confirms the query executes
    if(query.exec())
    {
        qDebug() << "Successfully added to wishlist";
    }
    else
    {
        qDebug() << query.lastError();
    }
    ui->treeWidget->clear();
    getMovieTitles();


}

void wishList::on_pushButton_2_clicked()
{
    QSqlQuery query(db);


    query.prepare("DELETE FROM Wishlist WHERE Title = (:title)");
    //Binds the appropriate values to the statement to avoid SQL Injection

    query.bindValue(":title", ui->comboBox->currentText());

    //Confirms the query executes
    if(query.exec())
    {
        QMessageBox::StandardButton error;

        error = QMessageBox::information(this,"ERROR:", "Deleted '"  + ui->comboBox->currentText()  + "' Movie");

    }
    else
    {
        qDebug() << query.lastError();
    }

    ui->treeWidget->clear();
    getMovieTitles();
}

void wishList::on_pushButton_3_clicked()
{
    getMovieTitles();
}



