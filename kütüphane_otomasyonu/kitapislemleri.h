//20010011066 Burcu Gül
#ifndef KITAPISLEMLERI_H
#define KITAPISLEMLERI_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class kitapislemleri;
}

class kitapislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit kitapislemleri(QWidget *parent = nullptr);
    ~kitapislemleri();

private slots:
    void on_btn_yeniKayit_clicked();

    void on_btn_guncelle_clicked();

    void on_btn_sil_clicked();

    void KitaplariGetir();
    void on_tw_kitaplar_clicked(const QModelIndex &index);

private:
    Ui::kitapislemleri *ui;
};

#endif // KITAPISLEMLERI_H
