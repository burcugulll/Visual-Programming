#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btn_uygula_clicked()
{
    QFont font;
    font.setFamily(ui->fontComboBox->currentText());
    font.setPointSize(ui->sB_yazibuyuklugu->value());
    QPalette renk;
    renk.setColor(QPalette::WindowText,ui->comboBoxrenk->currentText());
    font.setBold(ui->cB_bold->isChecked());
    font.setItalic(ui->cB_italik->isChecked());
    ui->label_yazigoster->setFont(font);
    ui->label_yazigoster->setPalette(renk);
    ui->label_yazigoster->setText(ui->ln_yazi->text());

}

