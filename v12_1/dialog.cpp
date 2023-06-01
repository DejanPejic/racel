#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup();

    timer = new QTimer(this); // Create the QTimer
    connect(timer, &QTimer::timeout, this, &Dialog::updateLCD); // Connect the timer to updateDisplay slot
    timer->start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}

double temperatura(void) 	//ocitavanje temperature
{
    FILE *ft;
    char tekst[100];
    ft = fopen("/sys/bus/w1/devices/28-000007237df2/w1_slave", "r");

    if (ft == NULL) return 0;

    int i = 0;
    for (i = 0; i < 22; i++)		//samo temperatura
        fscanf(ft, "%s", tekst);

    fclose(ft);

    //obrisati "t="
    for(i = 0; i < 10; i++) tekst[i] = tekst[i+2];

    int temp = atoi(tekst);
    double tem = (double) temp/1000;

    return tem;
}

void Dialog::updateLCD()
{
    //double value = 26 + ((double)(rand() % 20)) / 10;
    ui->lcdNumber->display(value);
}
