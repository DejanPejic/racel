#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>
#include <iostream>
#include <cstdio>

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup();

    Dialog::lcd = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

    connect(ui->pushButton, &QPushButton::clicked, this, &Dialog::printText);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::printText()
{
    QString text1 = ui->lineEdit1->text();
    QString text2 = ui->lineEdit2->text();
    //puts(text1.toLatin1().data());

    lcdClear(lcd);
    lcdPosition(Dialog::lcd, 0, 0);
    lcdPuts(Dialog::lcd, text1.toUtf8().constData());

    lcdPosition(Dialog::lcd, 0, 1);
    lcdPuts(Dialog::lcd, text2.toUtf8().constData());
    //puts(text1.toUtf8().constData());
    //fflush(stdout);
    //std::cout << qPrintable(text1) << std::endl;
    //
    //lcdPuts(lcd, text1.toLatin1().data());
    //lcdPosition(lcd, 0, 1);
    //lcdPuts(lcd, text2.toLatin1().data());
}
