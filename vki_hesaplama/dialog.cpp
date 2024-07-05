#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_buton_hesapla_clicked()
{
    int yil=ui->dateEdit->date().year();
    double boy=ui->dSB_boy->value();
    int kilo=ui->sB_kilo->value();
    int suankiyil=QDate::currentDate().year();
    int yas=suankiyil-yil;
    double vki;
    vki=kilo/(boy*boy);
    if(vki<18.5)
    {
        QMessageBox::information(this,"VKI Sonuç","<font color=red>Zayıf</font>,Yaş:"+QString::number(yas),"Tamam");
    }
    else if(vki<24.9)
    {
        QMessageBox::information(this,"VKI Sonuç","<font color=red>Normal Kilolu</font>,Yaş:"+QString::number(yas),"Tamam");
    }
     else if(vki<29.9)
    {
        QMessageBox::information(this,"VKI Sonuç","<font color=red>Fazla Kilolu</font>,Yaş:"+QString::number(yas),"Tamam");
    }
     else if(vki<39.9)
    {
        QMessageBox::information(this,"VKI Sonuç","<font color=red>Obez</font>,Yaş:"+QString::number(yas),"Tamam");
    }
    else
    {
        QMessageBox::information(this,"VKI Sonuç","<font color=red>İleri Derecede Obez</font>,Yaş:"+QString::number(yas),"Tamam");
    }
}

