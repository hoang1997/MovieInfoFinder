#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>

namespace Ui {
class createAccount;
}

class createAccount : public QDialog
{
    Q_OBJECT

public:
    explicit createAccount(QWidget *parent = nullptr);
    ~createAccount();

private slots:

    void on_create_acc_btn_clicked();

    void on_cancel_btn_clicked();

private:
    Ui::createAccount *ui;
};

#endif // CREATEACCOUNT_H
