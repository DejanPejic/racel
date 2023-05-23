#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

#include <wiringPi.h>
#include <lcd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int lcd;
    void printText();
};
#endif // DIALOG_H
