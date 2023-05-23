#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QTime>
#include <QTimer>

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
    void setTime();
    void updateDisplay();
    QTimer *timer;
};
#endif // DIALOG_H
