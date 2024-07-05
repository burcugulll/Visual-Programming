#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSql>
#include <QSqlTableModel>
#include <QMessageBox>
#include <personel.h>
#include <departman.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tableView_depart_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_depart_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase veritabani = QSqlDatabase::addDatabase("QSQLITE");
    QSqlTableModel *tablomodel;
    QSqlQueryModel *model;

};
#endif // MAINWINDOW_H
