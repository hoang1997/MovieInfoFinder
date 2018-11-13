#ifndef WISHLIST_H
#define WISHLIST_H

#include <QDialog>

namespace Ui {
class wishList;
}

class wishList : public QDialog
{
    Q_OBJECT

public:
    explicit wishList(QWidget *parent = nullptr);
    ~wishList();

private:
    Ui::wishList *ui;
};

#endif // WISHLIST_H
