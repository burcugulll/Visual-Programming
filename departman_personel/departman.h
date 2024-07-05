#ifndef DEPARTMAN_H
#define DEPARTMAN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSql>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class departman;
}

class departman : public QDialog
{
    Q_OBJECT

public:
    explicit departman(QSqlDatabase,QWidget *parent = nullptr);
    ~departman();
    void listele();

private slots:
    void on_tableView_depart_clicked(const QModelIndex &index);

    void on_pushButton_ekle_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

private:
    Ui::departman *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
};

#endif // DEPARTMAN_H
