#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_btn_rastgele_sayi_uret_clicked();

    void on_checkBox_tum_stateChanged(int arg1);

    void on_checkBox_asalcarpanlar_stateChanged(int arg1);

    void on_btn_listele_clicked();

    void on_btn_cikis_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
