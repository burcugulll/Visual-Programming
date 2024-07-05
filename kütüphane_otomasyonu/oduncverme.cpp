//20010011066 Burcu Gül
#include "oduncverme.h"
#include "ui_oduncverme.h"

oduncverme::oduncverme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oduncverme)
{
    ui->setupUi(this);

    QDate anlikTarih = QDate::currentDate();
    ui->dateEdit->setDate(anlikTarih);
    BilgileriGetir();
}

oduncverme::~oduncverme()
{
    delete ui;
}


void oduncverme::BilgileriGetir(){
    QSqlQuery query ;

    QSqlQueryModel *queryModel = new QSqlQueryModel();

    //üyeler table viewini güncelledik.
    query.exec("SELECT * FROM odunc_alinan");
    queryModel->setQuery(query);
    ui->tw_oduncAlinan->setModel(queryModel);

    QSqlQueryModel *queryModel2 = new QSqlQueryModel();
    //kitaplar table viewini güncelledik.
    query.exec("SELECT * FROM odunc_teslim_edilen");
    queryModel2->setQuery(query);
    ui->tw_teslimEdilen->setModel(queryModel2);




}


void oduncverme::on_btn_oduncVer_clicked()
{
    QString uyeNo = ui->le_uyeNo->text(),
            kitapNo = ui->le_kitapNo->text();

    QSqlQuery query ;

    QSqlQueryModel *queryModel = new QSqlQueryModel();

    //üyeler table viewini güncelledik.
    query.exec("SELECT * FROM odunc_alinan where uye_no = ? and kitap_no = ?");
    query.addBindValue(uyeNo);
    query.addBindValue(kitapNo);
    query.exec();

    queryModel->setQuery(query);
    ui->tw_oduncAlinan->setModel(queryModel);

    QString oduncAlinmaTarihi = queryModel->data(queryModel->index(0,3)).toString();


    QList tarihListesi = oduncAlinmaTarihi.split(".");
    std::reverse(tarihListesi.begin(),tarihListesi.end());
    int gun = tarihListesi[2].toInt(),ay = tarihListesi[1].toInt(),yil = tarihListesi[0].toInt();



    QDate oduncTarihi = QDate(yil,ay,gun);
    QDate teslimEdilen = ui->dateEdit->date();

    int gunFarki = oduncTarihi.daysTo(teslimEdilen);
    qDebug() << "Gün Farkı" << gunFarki;

    int borc = 0;
    if (gunFarki >= 15){
        borc = gunFarki-15;
    }


    query.prepare("INSERT INTO odunc_teslim_edilen (uye_no,kitap_no,alma_tarihi,verme_tarihi,borc)values(?,?,?,?,?)");
    query.addBindValue(uyeNo);
    query.addBindValue(kitapNo);
    query.addBindValue(oduncAlinmaTarihi);
    query.addBindValue(ui->dateEdit->text());
    query.addBindValue(borc);
    query.exec();


    //üyeler table viewini güncelledik.
    query.exec("DELETE FROM odunc_alinan where uye_no = ? and kitap_no = ?");
    query.addBindValue(uyeNo);
    query.addBindValue(kitapNo);
    query.exec();


    BilgileriGetir();

}


void oduncverme::on_tw_oduncAlinan_clicked(const QModelIndex &index)
{

    QString uyeNo = index.sibling(index.row(),1).data().toString();
    QString kitapNo = index.sibling(index.row(),2).data().toString();


    ui->le_uyeNo->setText(uyeNo);
    ui->le_kitapNo->setText(kitapNo);

}

