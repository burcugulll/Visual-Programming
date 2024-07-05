//20010011066 Burcu Gül
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uyeislemleri.h"
#include "kitapislemleri.h"
#include "oduncalma.h"
#include "oduncverme.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    uyeislemleri *uyeformu;
    kitapislemleri *kitapFormu;
    oduncalma *oduncAlFormu;
    oduncverme *oduncVerFormu;

    QSqlDatabase sqlite = QSqlDatabase::addDatabase("QSQLITE");


private slots:
    void on_btn_uyeIslemleri_clicked();

    void on_btn_kitapIslemleri_clicked();

    void on_btn_oduncAl_clicked();

    void on_btn_oduncTeslim_clicked();

    void ConnectDatabase();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
