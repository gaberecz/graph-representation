#include "prioritiesdialog.h"
#include "ui_prioritiesdialog.h"

PrioritiesDialog::PrioritiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrioritiesDialog)
{
    ui->setupUi(this);
    connect(ui->Size, SIGNAL(textChanged(QString)), this, SLOT(SetOkClickable(QString)));
    connect(ui->Ok, SIGNAL(clicked()), this, SLOT(OkButtonClicked()));
    connect(ui->Quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->priosRandom, SIGNAL(stateChanged(int)), this, SLOT(priorityRandomnessChanges()));

    ui->Ok->setEnabled(false);
    priolistLengthRandom = false;
    GraphSize = 0;

}

PrioritiesDialog::~PrioritiesDialog()
{
    delete ui;
}

void PrioritiesDialog::SetOkClickable(QString string) {
    if (string!="") {
        ui->Ok->setEnabled(true);
    } else {
        ui->Ok->setEnabled(false);
    }
}

void PrioritiesDialog::OkButtonClicked() {
    QString text = ui->Size->text();
    GraphSize = text.toInt();
    this->accept();
}

int PrioritiesDialog::getSize() {
    //qDebug() << "jártam itt";
    return GraphSize;
}

void PrioritiesDialog::priorityRandomnessChanges() {
    priolistLengthRandom = ui->priosRandom->isChecked();
}

bool PrioritiesDialog::isPriolistLengthRandom() {
    return priolistLengthRandom;
}
