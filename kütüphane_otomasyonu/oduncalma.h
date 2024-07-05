//20010011066 Burcu Gül
#ifndef ODUNCALMA_H
#define ODUNCALMA_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class oduncalma;
}

class oduncalma : public QDialog
{
    Q_OBJECT

public:
    explicit oduncalma(QWidget *parent = nullptr);
    ~oduncalma();

private slots:


    void on_btn_oduncAl_clicked();

    void on_tw_uyeler_clicked(const QModelIndex &index);

    void on_tw_kitaplar_clicked(const QModelIndex &index);

    void BilgileriGetir();

private:
    Ui::oduncalma *ui;
};

#endif // ODUNCALMA_H
