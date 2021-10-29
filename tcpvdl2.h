#ifndef TCPVDL2_H
#define TCPVDL2_H

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
class tcpvdl2;
}

class tcpvdl2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit tcpvdl2(QWidget *parent = nullptr);
    ~tcpvdl2();

private slots:
    void on_actionPARAM_req_triggered();

    void on_actionPWR_SET_REQ_triggered();

    void on_actionMODE_SET_REQ_triggered();

    void on_actionPURGRE_REQ_triggered();

    void on_actionPARAM_REQ_triggered();

    void on_actionMODE_SET_REQ_2_triggered();

    void on_pushButton_clicked();

    void on_UINT_DATA_REQ_clicked();

    void on_sqp_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_version_clicked();

    void start_timer();


private:
    Ui::tcpvdl2 *ui;
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

#endif // TCPVDL2_H
