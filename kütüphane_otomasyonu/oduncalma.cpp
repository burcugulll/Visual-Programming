//20010011066 Burcu Gül
#include "oduncalma.h"
#include "ui_oduncalma.h"

oduncalma::oduncalma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oduncalma)
{
    ui->setupUi(this);

    QDate anlikTarih = QDate::currentDate();
    ui->de_oduncAlmaTarihi->setDate(anlikTarih);
    BilgileriGetir();

}

oduncalma::~oduncalma()
{
    delete ui;
}


void oduncalma::BilgileriGetir(){
    QSqlQuery query ;

    QSqlQueryModel *queryModel = new QSqlQueryModel();

    //üyeler table viewini güncelledik.
    query.exec("SELECT * FROM uye");
    queryModel->setQuery(query);
    ui->tw_uyeler->setModel(queryModel);

    QSqlQueryModel *queryModel2 = new QSqlQueryModel();
    //kitaplar table viewini güncelledik.
    query.exec("SELECT * FROM kitap");
    queryModel2->setQuery(query);
    ui->tw_kitaplar->setModel(queryModel2);


    QSqlQueryModel *queryModel3 = new QSqlQueryModel();
    //ödünç alınan kitaplar table viewini güncelledik.
    query.exec("SELECT * FROM odunc_alinan");
    queryModel3->setQuery(query);
    ui->tw_oduncAlinanKitaplar->setModel(queryModel3);

}


void oduncalma::on_btn_oduncAl_clicked()
{
    QString uyeNo = ui->le_uyeNo->text(),
            kitapNo = ui->le_kitapNo->text(),
            oduncAlmaTarihi = ui->de_oduncAlmaTarihi->text();
    //qDebug() << uyeNo << kitapNo << oduncAlmaTarihi;
    QSqlQuery query ;

    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.prepare("select * from odunc_alinan where uye_no = ? and kitap_no = ?");
    query.addBindValue(uyeNo);
    query.addBindValue(kitapNo);
    query.exec();
    queryModel->setQuery(query);
    if(queryModel->rowCount() > 0){
        QMessageBox::information(this,"Hata!","Bu üye henüz kitabı teslim etmemiş.");
        return;
    }

    query.prepare("INSERT INTO odunc_alinan (uye_no,kitap_no,odunc_alma_tarihi) VALUES (?,?,?)");
    query.addBindValue(uyeNo);
    query.addBindValue(kitapNo);
    query.addBindValue(oduncAlmaTarihi);
    query.exec();
    BilgileriGetir();

}


void oduncalma::on_tw_uyeler_clicked(const QModelIndex &index)
{
    QString uyeNo = index.sibling(index.row(),0).data().toString();
    ui->le_uyeNo->setText(uyeNo);
}


void oduncalma::on_tw_kitaplar_clicked(const QModelIndex &index)
{
    QString kitapNo = index.sibling(index.row(),0).data().toString();
    ui->le_kitapNo->setText(kitapNo);
}

