#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->btn_asal_sayi,&QPushButton::clicked,this,&Dialog::Asal_sayi_bul);
    //connect(ui->pushButton_2,SIGNAL(clicked),this,SLOT(Cikis()));
   // connect(ui->btn_asal_sayi,SIGNAL(clicked),this,SLOT(Asal_sayi_bul()));
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Dialog::Cikis);
}

Dialog::~Dialog()
{
    delete ui;
}





/*void Dialog::on_btn_asal_sayi_clicked()
{
    ui->textBrowser_goster->clear();
    int sayi=ui->ln_sayi->text().toInt();
    int kontrol=0;
    for(int i=2; i<sayi; i++)
    {
        kontrol=0;
        for(int k=2; k<i; k++)
        {
            if(i%k==0)
            {
                kontrol=1;
            }
        }
        if(kontrol==0)
        {
            ui->textBrowser_goster->setText(ui->textBrowser_goster->toPlainText()+QString::number(i)+"\n");
        }
    }
}
*/
void Dialog::Asal_sayi_bul()
{
    ui->textBrowser_goster->clear();
    int sayi=ui->ln_sayi->text().toInt();
    int kontrol=0;
    for(int i=2; i<sayi; i++)
    {
        kontrol=0;
        for(int k=2; k<i; k++)
        {
            if(i%k==0)
            {
                kontrol=1;
            }
        }
        if(kontrol==0)
        {
            ui->textBrowser_goster->setText(ui->textBrowser_goster->toPlainText()+QString::number(i)+"\n");
        }
    }
}

void Dialog::Cikis()
{
    accept();
}

