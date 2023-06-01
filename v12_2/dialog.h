#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QTime>
#include <QTimer>

#include <iostream>
#include <cstdlib>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <wiringPi.h>
#include <wiringPiI2C.h>

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
    QTimer *timer;
    void update();
};
#endif // DIALOG_H
