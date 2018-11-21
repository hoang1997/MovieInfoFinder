#include "wishlist.h"
#include "ui_wishlist.h"

wishList::wishList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wishList)
{
    ui->setupUi(this);
}

wishList::~wishList()
{
    delete ui;
}
