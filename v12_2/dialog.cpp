#include "dialog.h"
#include "ui_dialog.h"

const char PCF8591 = 0x48;
int fd;
float vrednost;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup();
    fd = wiringPiI2CSetup(PCF8591);

    timer = new QTimer(this); // Create the QTimer
    connect(timer, &QTimer::timeout, this, &Dialog::update); // Connect the timer to updateDisplay slot
    timer->start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::update()
{
    int adcVal;
    int dial_value; // = rand() % 101;
    int slider_value; // = rand() % 101;
    float lcd_value; // = 26 + ((double)(rand() % 20)) / 10;

    int B = 3950;
    float t0 = 298.15;
    float R0 = 10000;
    float R1 = 1000;
    float Rt;

    adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3);
    dial_value = 100 * adcVal/255;
    ui->dial->setValue(dial_value);

    adcVal = wiringPiI2CReadReg8(fd, PCF8591);
    slider_value = 100 * adcVal/255;
    ui->verticalSlider->setValue(slider_value);

    adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 1);
    Rt = R1*adcVal/(256-adcVal);
    lcd_value = 1/(1/t0 + 1/B*log(Rt/R0)) - 273.15;
    ui->lcdNumber->display(lcd_value);
}
