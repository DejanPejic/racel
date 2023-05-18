#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

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

    // TODO: Set the RTCC time using the entered value
    // Replace the below line with the actual code to set the RTCC time
    QMessageBox::information(this, "Success", "RTCC time set successfully!");
    ui->label2->setText(timeString);
}

void Dialog::updateDisplay()
{
    // Update the QLabel text with the current time
    QTime currentTime = QTime::currentTime();
    QString timeText = currentTime.toString("hh:mm:ss");
    ui->label2->setText(timeText);
}
