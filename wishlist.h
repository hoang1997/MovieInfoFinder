#ifndef WISHLIST_H
#define WISHLIST_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>
#include <QDebug>
#include <QListWidget>
#include <QNetworkAccessManager>
#include <QMessageBox>

namespace Ui {
class wishList;
}

class wishList : public QDialog
{
    Q_OBJECT

public:
    explicit wishList(QWidget *parent = nullptr);
    ~wishList();

    void getMovieTitles();

    void setWishListMovie(QString,QString);

    void setPoster(QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();



private:
    Ui::wishList *ui;
    QVector<QString> movieTitles;
    QVector<QString> imdbIDs;
    QVector<QString> comments;
    QSqlDatabase db;
    QString posterPath;
};

#endif // WISHLIST_H

