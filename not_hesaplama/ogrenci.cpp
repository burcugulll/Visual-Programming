#include <QString>
#include <iostream>
class Ogrenci{
public:
    QString ad;
    QString soyad;
    int vize_not;
    int final_not;

    Ogrenci(QString ad,QString soyad,int vize_not,int final_not)
    {
        this->ad=ad;
        this->soyad=soyad;
        this->vize_not=vize_not;
        this->final_not=final_not;
    }
    double GecmeNotuHesapla(int vn,int fn)
    {
        double gecme_notu=(vn*0.4)+(fn*0.6);
        return gecme_notu;
    }

};
