#ifndef TCPACARS_H
#define TCPACARS_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QWidget>
#include <QTcpServer>
#include "histotcpacars.h"
#include <QUdpSocket>

namespace Ui {
class tcpacars;
}

class tcpacars : public QMainWindow
{
    Q_OBJECT

public:
    explicit tcpacars(QWidget *parent = nullptr);
    ~tcpacars();

private slots:
    void on_pushButton_clicked();

    void on_actionPARAM_REQ_triggered();

    void on_actionPARAM_REQ_2_triggered();

    void on_actionPWR_SET_REQ_triggered();

    void on_actionMODE_SET_REQ_triggered();

    void on_actionMODE_SET_REQ_2_triggered();

    void on_actionPURGE_REQ_triggered();

    void on_actionUNIT_DATA_REQ_triggered();

    void on_sqp_clicked();

private:
    Ui::tcpacars *ui;
    //QUdpSocket houda;
    QTcpServer *serverA;
    QTcpSocket *socketaacars;
    QTcpSocket *hd = new QTcpSocket();
    histotcpacars histotcpacars;



};

#endif // TCPACARS_H
