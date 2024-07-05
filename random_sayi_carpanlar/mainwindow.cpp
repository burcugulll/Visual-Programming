#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int randomsayi;
void MainWindow::on_btn_rastgele_sayi_uret_clicked()
{
    int altsinir,ustsinir;
    altsinir=ui->spinBox_altinir->value();
    ustsinir=ui->spinBox_ustsinir->value();
    if(altsinir>=ustsinir)
    {
        QMessageBox::information(this,"Uyarı!","Alt sınır üst sınırdan büyük ve eşit olamaz.Aralıkları kontrol ediniz!");
        return;
    }
    randomsayi=rand()%(ustsinir-altsinir)+altsinir;
    ui->label_randomsayi->setText("Üretilen Sayı: "+QString::number(randomsayi));

}


void MainWindow::on_checkBox_tum_stateChanged(int arg1)
{
    if (ui->listWidget_tum->isEnabled())
    {
        ui->listWidget_tum->setEnabled(false);
    }
    else
    {
        ui->listWidget_tum->setEnabled(true);
    }
}


void MainWindow::on_checkBox_asalcarpanlar_stateChanged(int arg1)
{
    if(ui->listWidget_asal->isEnabled())
    {
        ui->listWidget_asal->setEnabled(false);
    }
    else
    {
        ui->listWidget_asal->setEnabled(true);
    }
}


void MainWindow::on_btn_listele_clicked()
{
    if(ui->listWidget_tum->isEnabled())
    {
        ui->listWidget_tum->clear();
        for(int i=1; i<=randomsayi; i++)
        {
            if(randomsayi%i==0)
            {
                ui->listWidget_tum->addItem(QString::number(i));
            }
        }
    }
    int kontrol=0;
    if(ui->listWidget_asal->isEnabled())
    {
        ui->listWidget_asal->clear();
        for(int i=2; i<=randomsayi; i++)
        {
            kontrol=0;
            if(randomsayi%i==0)
            {
                for(int j=2; j<i; j++)
                {
                    if(i%j==0)
                    {
                        kontrol=1;
                    }
                }
                if(kontrol==0)
                {
                    ui->listWidget_asal->addItem(QString::number(i));
                }
            }
        }
    }

}


void MainWindow::on_btn_cikis_clicked()
{
    this->close();
}

