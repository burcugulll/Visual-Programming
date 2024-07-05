//20010011066 Burcu Gül
#ifndef ODUNCVERME_H
#define ODUNCVERME_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class oduncverme;
}

class oduncverme : public QDialog
{
    Q_OBJECT

public:
    explicit oduncverme(QWidget *parent = nullptr);
    ~oduncverme();

private slots:
    void on_btn_oduncVer_clicked();

    void on_tw_oduncAlinan_clicked(const QModelIndex &index);

    void BilgileriGetir();

private:
    Ui::oduncverme *ui;
};

#endif // ODUNCVERME_H
