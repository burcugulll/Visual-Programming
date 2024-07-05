#include "personel.h"
#include "ui_personel.h"

personel::personel(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personel)
{
    ui->setupUi(this);
    sorgu= new QSqlQuery(db);
    listele();

}

personel::~personel()
{
    delete ui;
}



void personel::listele()
{
    sorgu->prepare("select * from personel");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata",sorgu->lastError().text());
        return;
    }
    model= new QSqlQueryModel;
    model->setQuery(*sorgu);
    ui->tableView->setModel(model);
}


void personel::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_personid->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_personad->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_personsoyad->setText(model->index(index.row(),2).data().toString());
    ui->lineEdit_departid->setText(model->index(index.row(),3).data().toString());
}


void personel::on_pushButton_kaydet_clicked()
{
    sorgu->prepare("insert into personel(personel_ad,personel_soyad,departman_id) values(?,?,?)");
    sorgu->addBindValue(ui->lineEdit_personad->text());
    sorgu->addBindValue(ui->lineEdit_personsoyad->text());
    sorgu->addBindValue(ui->lineEdit_departid->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
    }
    listele();
}


void personel::on_pushButton_degistir_clicked()
{
    sorgu->prepare("update personel set personel_ad=?,personel_soyad=?,departman_id=? where personel_id=?");
    sorgu->addBindValue(ui->lineEdit_personad->text());
    sorgu->addBindValue(ui->lineEdit_personsoyad->text());
    sorgu->addBindValue(ui->lineEdit_departid->text().toInt());
    sorgu->addBindValue(ui->lineEdit_personid->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
    }
    listele();
}


void personel::on_pushButton_sil_clicked()
{
    sorgu->prepare("delete from personel where personel_id=?");
    sorgu->addBindValue(ui->lineEdit_personid->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!",sorgu->lastError().text());
    }
    listele();
}

