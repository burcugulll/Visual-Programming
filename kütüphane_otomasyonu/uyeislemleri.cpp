//20010011066 Burcu Gül
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

