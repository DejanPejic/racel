#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTime>
#include <QTimer>

#include<iostream>
#include<cstdlib>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

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
    void updateLCD();
    double temperatura();
};
#endif // DIALOG_H
