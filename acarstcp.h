#ifndef ACARSTCP_H
#define ACARSTCP_H

#include <QMainWindow>
#include<QLCDNumber>
#include<QSlider>
#include <QMainWindow>
#include <QLineEdit>
#include<QPushButton>
#include "form.h"
#include "version.h"
#include <QTcpSocket>
#include <QWidget>
#include <QTcpServer>
#include <QMainWindow>
#include <QTimer>
#include <QUdpSocket>
#include "form3.h"
#include "histovdltcp.h"
namespace Ui {
class acarstcp;
}

class acarstcp : public QMainWindow
{
    Q_OBJECT

public:
    explicit acarstcp(QWidget *parent = nullptr);
    ~acarstcp();

private:
    Ui::acarstcp *ui;
    form form;
    version version;
    QTcpServer *server;
    QTcpSocket *socketfd;
    QTcpSocket *socketfdR;
    QTimer *timer ;
    QUdpSocket *socketsqp;
    QUdpSocket *socketd;
    form3 form3;
    uint8_t counter =0;
    histovdltcp histovdltcp;

};

#endif // ACARSTCP_H
