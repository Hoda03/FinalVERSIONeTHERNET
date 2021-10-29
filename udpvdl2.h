#ifndef UDPVDL2_H
#define UDPVDL2_H

#include <QMainWindow>
#include <QtCharts>
#include <QMainWindow>
#include <QMainWindow>
#include <QWidget>
#include <QUdpSocket>
#include "histogramme.h"
#include "form.h"
#include "version.h"

using namespace std;

#define SIZE_BUFF_RXDATA         8196
#define SIZE_BUFF_DSPDATA        16384
#define SIZE_BUFF_TXDATA         8196
#define SIZE_SYNCHRO_VDL2     4
#define ACARSIP_ACARSIP       0xF2
#define ACARSIP_PID_UNIT_DATA_REQ    0x21   /* TX  */
/*----------------------------Définition de la structure des primitives ACARS  en liaison UDP------------------------------------*/


struct tsPid20vdl {
    uint8_t synchro[SIZE_SYNCHRO_VDL2];
    uint8_t mode;
    uint8_t pid;
    uint8_t dfl1_msb;
    uint8_t dfl2_lsb;
    uint8_t freq_msb;
    uint8_t freq_lsb;
    uint8_t tm1;
    uint8_t tm2;
    uint8_t M1_msb;
    uint8_t M1_lsb;
    uint8_t persistance;
    uint16_t crc;
};

struct tsPidF0vdl{
    uint8_t synchro[SIZE_SYNCHRO_VDL2];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t mode;
    uint8_t req;
    uint16_t crc;

};
struct tsPidF1vdl {
    uint8_t synchro[SIZE_SYNCHRO_VDL2];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t pwr;
    uint8_t req;
    uint16_t crc;

};
struct tsPid010bvdl {
    uint8_t synchro[SIZE_SYNCHRO_VDL2];
    uint8_t sal;
    uint8_t donnees;
    uint8_t pid;
    uint8_t protocoelCode;
    uint16_t crc;

};

namespace Ui {
class udpvdl2;
}

class udpvdl2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit udpvdl2(QWidget *parent = nullptr);
    ~udpvdl2();

private slots:
    void on_sqp_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_transmission_ratio_clicked();

    void on_pushButton_3_clicked();

    void on_version_clicked();

    void on_pushButton_2_clicked();

    void on_actionPARAM_REQ_triggered();

    void on_actionPWR_SET_REQ_triggered();

    void on_actionMODE_SET_REQ_triggered();

    void on_actionPURGE_REQ_triggered();

    void on_actionPARAM_REQ_2_triggered();

    void on_actionMODE_SET_REQ_2_triggered();

private:
    Ui::udpvdl2 *ui;
    QUdpSocket *mSocket;
    QHostAddress sender;
    quint16 senderPort;
    uint8_t counter =0;
    uint8_t counter1 =0;

    QChartView *graphique; // un widget pour afficher un graphe
    QChart *graphe; // la représentation d'un graphe
    QLineSeries *courbe; // les données
    histogramme histogramme;
    QLineEdit hostaddress1_6;
    QLineEdit hostaddress1_5;
    QSpinBox port1_6;
    QSpinBox port1_5;
    //reptransudpvdl reptransudpvdl;
    form form ;
    version version;
};

#endif // UDPVDL2_H
