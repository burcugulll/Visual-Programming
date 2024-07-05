#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    veritabani.setDatabaseName("C:/Users/Burcu/Downloads/sirket.db");
    if(veritabani.open())
    {
       // QSqlQuery sorgu;
       //model= new QSqlQueryModel;
       //sorgu.exec("select * from departman");
       // model->setQuery(sorgu);
       // ui->tableView_depart->setModel(model);
       ui->statusbar->showMessage("Veri tabanına bağlanıldı.");
       tablomodel=new QSqlTableModel;
       tablomodel->setTable("departman");
       tablomodel->select();
       ui->tableView_depart->setModel(tablomodel);


    }
    else
        ui->statusbar->showMessage("Veri tabanına bağlanılamadı.");



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tableView_depart_clicked(const QModelIndex &index)
{
    QString indis=tablomodel->index(index.row(),0).data().toString();
    //int indis2=indis.toInt();
    QSqlQuery sorgu;
    sorgu.prepare("select * from personel where departman_id=?");
    sorgu.addBindValue(indis);
    sorgu.exec();
    model=new QSqlQueryModel;
    model->setQuery(sorgu);
    ui->tableView_person->setModel(model);


}


void MainWindow::on_pushButton_clicked()
{
    personel *personeller=new personel(veritabani);
    personeller->show();
}


void MainWindow::on_pushButton_depart_clicked()
{
    departman *departmanlar = new departman(veritabani);
    departmanlar->show();
}

