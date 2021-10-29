#ifndef ACCEUIL_H
#define ACCEUIL_H

#include <QMainWindow>
#include "udpacars.h"
#include "tcpvdl2.h"
//#include "acarstcp.h"


namespace Ui {
class acceuil;
}

class acceuil : public QMainWindow
{
    Q_OBJECT

public:
    explicit acceuil(QWidget *parent = nullptr);
    ~acceuil();

private slots:
    void on_acarsvdl2_clicked();

private:
    Ui::acceuil *ui;
    tcpvdl2 tcpvdl2;
    udpacars udpacars;
  //  acarstcp acarstcp;
};

#endif // ACCEUIL_H
