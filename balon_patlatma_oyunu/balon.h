#ifndef BALON_H
#define BALON_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
class balon : public QPushButton
{
    Q_OBJECT
public:
    balon();
    int deletemrq;
    int kontrol;
    explicit balon(QWidget *parent=0);
    bool dgdm;
signals:


private:

public slots:
    void dlte();
    void bumbum();
    void dokunus();

};

#endif // BALON_H
