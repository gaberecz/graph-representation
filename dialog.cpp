#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->Size, SIGNAL(textChanged(QString)), this, SLOT(SetOkClickable(QString)));
    connect(ui->Ok, SIGNAL(clicked()), this, SLOT(OkButtonClicked()));
    connect(ui->Quit, SIGNAL(clicked()), this, SLOT(close()));

    ui->Ok->setEnabled(false);
    GraphSize = 0;

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SetOkClickable(QString string) {
    if (string!="") {
        ui->Ok->setEnabled(true);
    } else {
        ui->Ok->setEnabled(false);
    }
}

void Dialog::OkButtonClicked() {
    QString text = ui->Size->text();
    GraphSize = text.toInt();
    this->accept();
}

int Dialog::getSize() {
    //qDebug() << "jártam itt";
    return GraphSize;
}
