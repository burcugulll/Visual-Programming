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


#include "uyeislemleri.h"
#include "ui_uyeislemleri.h"

uyeislemleri::uyeislemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uyeislemleri)
{
    ui->setupUi(this);
    UyeleriGetir();
}


uyeislemleri::~uyeislemleri()
{
    delete ui;
}

void uyeislemleri::UyeleriGetir(){
    QSqlQuery query ;

    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.exec("SELECT * FROM uye");
    queryModel->setQuery(query);
    ui->tw_uyeler->setModel(queryModel);

}




void uyeislemleri::on_btn_yeniKayit_clicked()
{
    QString uyeAd = ui->le_uyeAd->text() , uyeSoyad = ui->le_uyeSoyad->text();

    if(uyeAd == "" || uyeSoyad == ""){
        QMessageBox::critical(this,"Hata!","Gerekli alanları doldurunuz!","Ok");
        return;
    }

    QSqlQuery query ;
    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.prepare("INSERT INTO uye (uye_ad,uye_soyad) VALUES (?,?)");
    query.addBindValue(uyeAd);
    query.addBindValue(uyeSoyad);
    query.exec();

    UyeleriGetir();

    ui->le_uyeNo->setText("");
    ui->le_uyeAd->setText("");
    ui->le_uyeSoyad->setText("");

    QMessageBox::information(this,"Yeni Kayıt","Kayıt başarıyla eklendi");
}


void uyeislemleri::on_btn_guncelle_clicked()
{
    QString uyeAd = ui->le_uyeAd->text() , uyeSoyad = ui->le_uyeSoyad->text();
    QString uyeNo = ui->le_uyeNo->text();

    if(uyeAd == "" || uyeSoyad == ""){
        QMessageBox::critical(this,"Hata","Gerekli Alanları Doldurunuz!","Ok");
        return;
    }

    QSqlQuery query ;
    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.prepare("UPDATE uye SET uye_ad = (?),uye_soyad = (?) WHERE uye_no=(?)");
    query.addBindValue(uyeAd);
    query.addBindValue(uyeSoyad);
    query.addBindValue(uyeNo);
    query.exec();

    UyeleriGetir();

    ui->le_uyeNo->setText("");
    ui->le_uyeAd->setText("");
    ui->le_uyeSoyad->setText("");

    QMessageBox::information(this,"Kayıt Güncelle","Kayıt başarıyla güncellendi");
}



void uyeislemleri::on_btn_sil_clicked()
{
    QString uyeAd = ui->le_uyeAd->text() , uyeSoyad = ui->le_uyeSoyad->text();
    QString uyeNo = ui->le_uyeNo->text();

    if(uyeAd == "" || uyeSoyad == "" || uyeNo == ""){
        QMessageBox::critical(this,"Hata","Silinecek Kaydı Seçin!","Ok");
        return;
    }


    QSqlQuery query ;
    QSqlQueryModel *queryModel = new QSqlQueryModel();


    query.prepare("SELECT * FROM odunc_alinan WHERE uye_no = (?)");
    query.addBindValue(uyeNo);
    query.exec();
    queryModel->setQuery(query);

    if(queryModel->rowCount() > 0){
        QMessageBox::information(this,"Hata!","Bu üye silinemez. Bu üye üstüne tanımlanmış kitaplar var!");
        return;
    }


    query.prepare("DELETE FROM uye WHERE uye_no = (?)");
    query.addBindValue(uyeNo);
    query.exec();

    UyeleriGetir();

    ui->le_uyeNo->setText("");
    ui->le_uyeAd->setText("");
    ui->le_uyeSoyad->setText("");

    QMessageBox::information(this,"Kayıt Güncelle","Kayıt başarıyla silindi");

}


void uyeislemleri::on_tw_uyeler_clicked(const QModelIndex &index)
{
    QString uyeAd,uyeSoyad;
    QString uyeNo = index.sibling(index.row(),0).data().toString();
    // tabloda hangi satıra tıklanırsa tıklansın onun ogr numarasını almak için yaptım


    QSqlQuery query ;
    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.prepare("SELECT * FROM uye WHERE uye_no = (?)");
    query.addBindValue(uyeNo);
    query.exec();
    queryModel->setQuery(query);

    uyeAd = queryModel->data(queryModel->index(0,1)).toString();
    uyeSoyad = queryModel->data(queryModel->index(0,2)).toString();

    ui->le_uyeNo->setText(uyeNo);
    ui->le_uyeAd->setText(uyeAd);
    ui->le_uyeSoyad->setText(uyeSoyad);


}

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


#include "kitapislemleri.h"
#include "ui_kitapislemleri.h"

kitapislemleri::kitapislemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kitapislemleri)
{
    ui->setupUi(this);
    KitaplariGetir();
}

kitapislemleri::~kitapislemleri()
{
    delete ui;
}

void kitapislemleri::KitaplariGetir(){
    QSqlQuery query ;

    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.exec("SELECT * FROM kitap");
    queryModel->setQuery(query);
    ui->tw_kitaplar->setModel(queryModel);

}




void kitapislemleri::on_btn_yeniKayit_clicked()
{
    QString kitapAd = ui->le_kitapAd->text() , stok = ui->le_stok->text();

    if(kitapAd == "" || stok == ""){
        QMessageBox::critical(this,"Hata","Gerekli Alanları Doldurunuz!","Ok");
        return;
    }

    QSqlQuery query ;
    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.prepare("INSERT INTO kitap (kitap_ad,kitap_sayisi) VALUES (?,?)");
    query.addBindValue(kitapAd);
    query.addBindValue(stok);
    query.exec();

    KitaplariGetir();

    ui->le_kitapNo->setText("");
    ui->le_kitapAd->setText("");
    ui->le_stok->setText("");

    QMessageBox::information(this,"Yeni Kayıt","Kayıt başarıyla eklendi");
}


void kitapislemleri::on_btn_guncelle_clicked()
{
    QString kitapAd = ui->le_kitapAd->text() , stok = ui->le_stok->text();
    QString kitapNo = ui->le_kitapNo->text();

    if(kitapAd == "" || stok == ""){
        QMessageBox::critical(this,"Hata","Gerekli Alanları Doldurunuz!","Ok");
        return;
    }

    QSqlQuery query ;
    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.prepare("UPDATE kitap SET kitap_ad = (?),kitap_sayisi = (?) WHERE kitap_no=(?)");
    query.addBindValue(kitapAd);
    query.addBindValue(stok);
    query.addBindValue(kitapNo);
    query.exec();

    KitaplariGetir();

    ui->le_kitapNo->setText("");
    ui->le_kitapAd->setText("");
    ui->le_stok->setText("");

    QMessageBox::information(this,"Kayıt Güncelle","Kayıt başarıyla güncellendi");
}


void kitapislemleri::on_btn_sil_clicked()
{
    QString kitapAd = ui->le_kitapAd->text() , stok = ui->le_stok->text();
    QString kitapNo = ui->le_kitapNo->text();

    if(kitapAd == "" || stok == "" || kitapNo == ""){
        QMessageBox::critical(this,"Hata","Silinecek Kaydı Seçin!","Ok");
        return;
    }


    QSqlQuery query ;
    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.prepare("SELECT * FROM odunc_alinan WHERE kitap_no = (?)");
    query.addBindValue(kitapNo);
    query.exec();
    queryModel->setQuery(query);
    if(queryModel->rowCount() > 0){
        QMessageBox::information(this,"Hata!","Bu kitap silinemez. Bu kitap bazı üyeler tarafından ödünç alınmış!");
        return;
    }


    query.prepare("DELETE FROM kitap WHERE kitap_no = (?)");
    query.addBindValue(kitapNo);
    query.exec();

    KitaplariGetir();

    ui->le_kitapNo->setText("");
    ui->le_kitapAd->setText("");
    ui->le_stok->setText("");

    QMessageBox::information(this,"Kayıt Güncelle","Kayıt başarıyla silindi");

}


void kitapislemleri::on_tw_kitaplar_clicked(const QModelIndex &index)
{
    QString kitapAd,stok;
    QString kitapNo = index.sibling(index.row(),0).data().toString();
    // tabloda hangi satıra tıklanırsa tıklansın onun ogr numarasını almak için yaptım


    QSqlQuery query ;
    QSqlQueryModel *queryModel = new QSqlQueryModel();

    query.prepare("SELECT * FROM kitap WHERE kitap_no = (?)");
    query.addBindValue(kitapNo);
    query.exec();
    queryModel->setQuery(query);



    kitapAd = queryModel->data(queryModel->index(0,1)).toString();
    stok = queryModel->data(queryModel->index(0,2)).toString();

    QSqlQueryModel *queryOduncModel = new QSqlQueryModel();
    query.prepare("SELECT * FROM odunc_alinan WHERE kitap_no = (?)");
    query.addBindValue(kitapNo);
    query.exec();

    queryOduncModel->setQuery(query);

    ui->tw_oduncAlinma->setModel(queryOduncModel);


    QSqlQueryModel *queryOnceOduncModel = new QSqlQueryModel();
    query.prepare("SELECT * FROM odunc_teslim_edilen WHERE kitap_no = (?)");
    query.addBindValue(kitapNo);
    query.exec();

    queryOnceOduncModel->setQuery(query);

    ui->tw_oncedenOdunc->setModel(queryOnceOduncModel);


    ui->le_kitapNo->setText(kitapNo);
    ui->le_kitapAd->setText(kitapAd);
    ui->le_stok->setText(stok);

}

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
