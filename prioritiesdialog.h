#ifndef PRIODIALOG_H
#define PRIODIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class PrioritiesDialog;
}

class PrioritiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrioritiesDialog(QWidget *parent = 0);
    ~PrioritiesDialog();
    int getSize();
    bool isPriolistLengthRandom();

private:
    Ui::PrioritiesDialog *ui;
    int GraphSize;
    bool priolistLengthRandom;
public slots:
    void OkButtonClicked();
    void SetOkClickable(QString string);
    void priorityRandomnessChanges();
};

#endif // PRIODIALOG_H
