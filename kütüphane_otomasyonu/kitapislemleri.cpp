//20010011066 Burcu Gül
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

