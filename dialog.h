#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    int getSize();

private:
    Ui::Dialog *ui;
    int GraphSize;
public slots:
    void OkButtonClicked();
    void SetOkClickable(QString string);
};

#endif // DIALOG_H
