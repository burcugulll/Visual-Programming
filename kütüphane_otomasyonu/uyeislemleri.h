//20010011066 Burcu Gül
#ifndef UYEISLEMLERI_H
#define UYEISLEMLERI_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class uyeislemleri;
}

class uyeislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit uyeislemleri(QWidget *parent = nullptr);
    ~uyeislemleri();

private slots:
    void on_btn_yeniKayit_clicked();

    void on_btn_guncelle_clicked();

    void on_btn_sil_clicked();

    void UyeleriGetir();

    void on_tw_uyeler_clicked(const QModelIndex &index);

private:
    Ui::uyeislemleri *ui;
};

#endif // UYEISLEMLERI_H
