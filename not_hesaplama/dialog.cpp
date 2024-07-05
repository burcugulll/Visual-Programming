#include "dialog.h"
#include "ui_dialog.h"
#include "ogrenci.cpp"
QList<Ogrenci*>ogrler;
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QFile my_file("gecenler.txt");
    if(!my_file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Hata!","Dosya Açılamadı","Ok");
        return;
    }
    QTextStream stream(&my_file);
    while(!stream.atEnd())//stream dosyanın sonunda değilse
    {
        ui->listWidget->addItem(stream.readLine());
    }
    my_file.close();

    QFile my_file2("kalanlar.txt");
    if(!my_file2.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Hata!","Dosya Açılamadı","Ok");
        return;
    }
    QTextStream stream2(&my_file2);
    while(!stream2.atEnd())
    {
        ui->listWidget_2->addItem(stream2.readLine());
    }
    my_file2.close();


}

Dialog::~Dialog()
{
    QFile my_file3("tumogrenciler.txt");
    if(!my_file3.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Hata!",my_file3.errorString(),"Ok");
        return;
    }
    QTextStream stream3(&my_file3);
    foreach(Ogrenci *ogr,ogrler)
    {
        stream3<<ogr->ad+" "+ogr->soyad+" "+"Gecme Notu:"+QString::number(ogr->GecmeNotuHesapla(ogr->vize_not,ogr->final_not))+"\n";
    }
    delete ui;

}


void Dialog::on_pushButton_clicked()
{
    Ogrenci *ogr=new Ogrenci(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text().toInt(),ui->lineEdit_4->text().toInt());
    ogrler.append(ogr);
    double gn=ogr->GecmeNotuHesapla(ogr->vize_not,ogr->final_not);
    if(ogr->GecmeNotuHesapla(ogr->vize_not,ogr->final_not)>=60)
    {
        ui->listWidget->addItem(ogr->ad+" "+ogr->soyad+" "+"Gecme Notu:"+QString::number(gn));
    }
    else
    {
        ui->listWidget_2->addItem(ogr->ad+" "+ogr->soyad+" "+"Gecme Notu:"+QString::number(gn));
    }
}

