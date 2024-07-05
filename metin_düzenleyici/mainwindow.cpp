#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    ui->plainTextEdit->clear();
    this->statusBar()->showMessage("New File!");
}


void MainWindow::on_actionOpen_triggered()
{
    QString path=QFileDialog::getOpenFileName(this,"Open a File!");
    QFile my_file(path);
    if(!my_file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error!",my_file.errorString());
        return;
    }
    QTextStream stream(&my_file);
    ui->plainTextEdit->setPlainText(stream.readAll());
    my_file.close();
    this->statusBar()->showMessage(path);
}


void MainWindow::on_actionSave_triggered()
{
    QString path=QFileDialog::getSaveFileName(this,"Save a File!");
    QFile my_file(path);
    if(!my_file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error!",my_file.errorString());
        return;
    }
    QTextStream stream(&my_file);
    stream <<ui->plainTextEdit->toPlainText();
    my_file.close();
    this->statusBar()->showMessage(path);
}


void MainWindow::on_actionExit_triggered()
{
   this->close();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionSelect_All_triggered()
{
    ui->plainTextEdit->selectAll();
}


void MainWindow::on_actionSelect_None_triggered()
{
    QTextCursor my_cursor=ui->plainTextEdit->textCursor();
    my_cursor.movePosition(QTextCursor::End);
    ui->plainTextEdit->setTextCursor(my_cursor);
}

void MainWindow::on_actionToolbar_Bottom_triggered()
{
    addToolBar(Qt::BottomToolBarArea,ui->toolBar);
}



void MainWindow::on_actionToolBar_Top_triggered()
{
    addToolBar(Qt::TopToolBarArea,ui->toolBar);
}


void MainWindow::on_actionToolbar_Right_triggered()
{
    addToolBar(Qt::RightToolBarArea,ui->toolBar);
}


void MainWindow::on_actionToolbar_Left_triggered()
{
    addToolBar(Qt::LeftToolBarArea,ui->toolBar);

}


void MainWindow::on_actionToolbar_Floatable_triggered()
{
    ui->toolBar->setFloatable(false);
}


void MainWindow::on_actionToolbar_Movable_triggered()
{
    ui->toolBar->setMovable(false);
}


void MainWindow::on_actionOpen_Form_triggered()
{
    MainWindow2 *mw2=new MainWindow2(this);
    mw2->show();
}

