#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>

#define changeHexToInt(hex) ((((hex)>>4)*10)+((hex)%16))
#define changeIntToHex(int) (((int/10)<<4)+(int%10))

// adrese registara
#define SEK 0x02
#define MINUT 0x03
#define SAT 0x04
#define DAN 0x05
#define RDAN 0x06
#define MES 0x07
#define GDN 0x08

unsigned char WriteBuf[2];
unsigned char ReadBuf;
unsigned char g8563_Store[7];
// inicijalna vrednost           sek    min  sat   dan   rds   msc   gdn
unsigned char init8563_Store[7]={0x00, 0x00, 0x00, 0x30, 0x03, 0x03, 0x23};

int fd;

void P8563_settime(int fd)
{
    WriteBuf[0] = SEK;
    WriteBuf[1] = g8563_Store[0];
    wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);

    WriteBuf[0] = MINUT;
    WriteBuf[1] = g8563_Store[1];
    wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);

    WriteBuf[0] = SAT;
    WriteBuf[1] = g8563_Store[2];
    wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);

    WriteBuf[0] = DAN;
    WriteBuf[1] = g8563_Store[3];
    wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);

    WriteBuf[0] = RDAN;
    WriteBuf[1] = g8563_Store[4];
    wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);

    WriteBuf[0] = MES;
    WriteBuf[1] = g8563_Store[5];
    wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);
// WiringPiI2CReg
    WriteBuf[0] = GDN;
    WriteBuf[1] = g8563_Store[6];
    wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);
}

void P8563_init()
{
    unsigned char i;

    for(i = 0; i <= 7; i++)
        g8563_Store[i] = init8563_Store[i];

    P8563_settime(fd);
    printf("Postavi pocetno tekuce vreme\n");

    //inicijalizacija RTC-a
    WriteBuf[0] = 0x0;
    WriteBuf[1] = 0x00; // normalni rezim rada
    wiringPiI2CWriteReg16(fd, WriteBuf[0], WriteBuf[1]);
}

void P8563_Readtime()
{
    WriteBuf[0] = SEK;
    g8563_Store[0] = wiringPiI2CReadReg8(fd, WriteBuf[0]) & 0x7f;

    WriteBuf[0] = MINUT;
    g8563_Store[1] = wiringPiI2CReadReg8(fd, WriteBuf[0]) & 0x7f;

    WriteBuf[0] = SAT;
    g8563_Store[2] = wiringPiI2CReadReg8(fd, WriteBuf[0]) & 0x3f;

    WriteBuf[0] = DAN;
    g8563_Store[3] = wiringPiI2CReadReg8(fd, WriteBuf[0]) & 0x3f;

    WriteBuf[0] = RDAN;
    g8563_Store[4] = wiringPiI2CReadReg8(fd, WriteBuf[0]) & 0x07;

    WriteBuf[0] = MES;
    g8563_Store[5] = wiringPiI2CReadReg8(fd, WriteBuf[0]) & 0x1f;

    WriteBuf[0] = GDN;
    g8563_Store[6] = wiringPiI2CReadReg8(fd, WriteBuf[0]) & 0xff;

    g8563_Store[0] = changeHexToInt(g8563_Store[0]);
    g8563_Store[1] = changeHexToInt(g8563_Store[1]);
    g8563_Store[2] = changeHexToInt(g8563_Store[2]);
    g8563_Store[3] = changeHexToInt(g8563_Store[3]);
    g8563_Store[4] = changeHexToInt(g8563_Store[4]);
    g8563_Store[5] = changeHexToInt(g8563_Store[5]);
    g8563_Store[6] = changeHexToInt(g8563_Store[6]);
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    fd = wiringPiI2CSetup(0x51);

    if (fd == -1)
    {
        printf("NE RADI I2C\n");
    }

    P8563_init();

    timer = new QTimer(this); // Create the QTimer
    connect(timer, &QTimer::timeout, this, &Dialog::updateDisplay); // Connect the timer to updateDisplay slot
    timer->start(1000);

    connect(ui->pushButton, &QPushButton::clicked, this, &Dialog::setTime);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setTime()
{
    QString timeString = ui->lineEdit->text();

    QTime enteredTime = QTime::fromString(timeString, "hh:mm:ss");

    if (!enteredTime.isValid()) {
        QMessageBox::warning(this, "Invalid Time", "Invalid time format. Please enter time in HH:MM:SS format.");
        return;
    }

    int hours = enteredTime.hour();
    int minutes = enteredTime.minute();
    int seconds = enteredTime.second();

    init8563_Store[0] = changeIntToHex(seconds);
    init8563_Store[1] = changeIntToHex(minutes);
    init8563_Store[2] = changeIntToHex(hours);

    P8563_init();

    // TODO: Set the RTCC time using the entered value
    // Replace the below line with the actual code to set the RTCC time
    QMessageBox::information(this, "Success", "RTCC time set successfully!");
    ui->label2->setText(timeString);
}

void Dialog::updateDisplay()
{
    P8563_Readtime();
    int sekunde = g8563_Store[0];
    int minuti= g8563_Store[1];
    int sati = g8563_Store[2];

    // Update the QLabel text with the current time
    QTime currentTime(sati, minuti, sekunde, 0);
    QString timeText = currentTime.toString("hh:mm:ss");
    ui->label2->setText(timeText);
}
