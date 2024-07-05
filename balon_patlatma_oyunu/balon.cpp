#include "balon.h"
#include <QRandomGenerator>
#include <QDebug>
balon::balon(QWidget *parent):
    QPushButton(parent)
{
    dgdm = false;
    kontrol = 1;
    deletemrq = 0;
    connect(this,SIGNAL(clicked()),this,SLOT(dokunus()));
}
void balon::dlte()
{
    deletemrq = 0;

}
void balon::bumbum()
{
   kontrol = 0;
}
void balon::dokunus()
{
    dgdm=!dgdm;
}

