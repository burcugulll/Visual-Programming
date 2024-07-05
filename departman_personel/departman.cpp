#include "departman.h"
#include "ui_departman.h"

departman::departman(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::departman)
{
    ui->setupUi(this);
    sorgu= new QSqlQuery(db);
    listele();
}

departman::~departman()
{
    delete ui;
}

void departman::listele()
{
    sorgu->prepare("select * from departman");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text());
        return;
    }
    model= new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_depart->setModel(model);
}

void departman::on_tableView_depart_clicked(const QModelIndex &index)
{
    ui->lineEdit_id->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_ad->setText(model->index(index.row(),1).data().toString());
}


void departman::on_pushButton_ekle_clicked()
{
    sorgu->prepare("insert into departman (departman_ad) values(?)");
    sorgu->addBindValue(ui->lineEdit_ad->text());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
    }
    listele();
}


void departman::on_pushButton_guncelle_clicked()
{
    sorgu->prepare("update departman set departman_ad=? where departman_id=?");
    sorgu->addBindValue(ui->lineEdit_ad->text());
    sorgu->addBindValue(ui->lineEdit_id->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
    }
    listele();
}


void departman::on_pushButton_sil_clicked()
{
    sorgu->prepare("select * from personel where departman_id=?");
    sorgu->addBindValue(ui->lineEdit_id->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
    }
    int sayac=0;
    while(sorgu->next())
    {
        sayac+=1;
    }
    if(sayac>0)
    {
        QMessageBox::critical(this,"Hata!","Bu departmana ait personel bulunmakta silinemez.");

    }
    else
    {
        sorgu->prepare("delete from departman where departman_id=?");
        sorgu->addBindValue(ui->lineEdit_id->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
        }
        listele();
    }

}

