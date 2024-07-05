//20010011066 Burcu Gül
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uyeislemleri.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConnectDatabase();
}

MainWindow::~MainWindow()
{
    sqlite.commit();
    delete ui;
}


void MainWindow::ConnectDatabase(){
    sqlite.setDatabaseName("C:/Users/Burcu/Documents/Qt/gorselprog2023/20010011066/20010011066.db");

    if(!sqlite.open()){
        ui->statusbar->showMessage("Veri Tabanına Bağlanılamadı");
        return;
    }else{
        ui->statusbar->showMessage("Veri Tabanına Başarıyla Bağlanıldı");
    }

}


void MainWindow::on_btn_uyeIslemleri_clicked()
{
    uyeformu = new uyeislemleri(this);
    uyeformu->show();
}


void MainWindow::on_btn_kitapIslemleri_clicked()
{
    kitapFormu = new kitapislemleri(this);
    kitapFormu->show();
}


void MainWindow::on_btn_oduncAl_clicked()
{
    oduncAlFormu = new oduncalma(this);
    oduncAlFormu->show();
}


void MainWindow::on_btn_oduncTeslim_clicked()
{
    oduncVerFormu = new oduncverme(this);
    oduncVerFormu->show();
}

