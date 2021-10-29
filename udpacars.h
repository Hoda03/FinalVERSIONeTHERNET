#ifndef UDPACARS_H
#define UDPACARS_H
#include <QMainWindow>
#include <QtCharts>
#include <QMainWindow>
#include <QWidget>
#include <QUdpSocket>
#include "histogramme.h"
#include <QMainWindow>
#include <QWidget>
#include "histoacarsudp.h"
#include "form1.h"
#include "version.h"
#include <QUdpSocket>
#include <QByteArray>

const uint8_t synchroAcars[4] = {0xff,0x00,0xf0,0xca};
constexpr size_t sizeh =10;

#define SIZE_BUFF_RXDATA         8196
#define SIZE_BUFF_DSPDATA        16384
#define SIZE_BUFF_TXDATA         8196
#define SIZE_SYNCHRO_ACARS     4
#define address_ACARS     7

#define ACARSIP_ACARSIP       0xF2
#define ACARSIP_PID_UNIT_DATA_REQ    0x21   /* TX  */

#if  __cplusplus > 199711L
      #define register
#endif

/*----------------------------Définition de la structure des primitives ACARS  en liaison UDP------------------------------------*/
struct tsPid55{
    uint8_t synchro[SIZE_SYNCHRO_ACARS];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t status;
    uint16_t crc;

};

struct tsPid21{
    uint8_t synchro[SIZE_SYNCHRO_ACARS];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t donnees;
    uint8_t sufBcs;
    uint8_t soh;
    uint8_t mode;
    uint8_t address1;
    uint8_t address2;
    uint8_t address3;
    uint8_t address4;
    uint8_t address5;
    uint8_t address6;
    uint8_t address7;
    uint8_t ack;
    uint8_t label1;
    uint8_t label2;
    uint8_t bi;
    uint8_t stx;
    char str1[220];
    uint8_t suff;
    uint8_t bcs;
    uint8_t DE;
    uint8_t bcsSuff;
    uint16_t crc;
    uint8_t msn;
    uint8_t flightid;



};
struct tsPidF1{
    uint8_t synchro[SIZE_SYNCHRO_ACARS];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t pwr;
    uint8_t req;
    uint16_t crc;

};

struct tsPidF0{
    uint8_t synchro[SIZE_SYNCHRO_ACARS];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t mode;
    uint8_t req;
    uint16_t crc;

};
struct tsPid20 {

    uint8_t synchro[SIZE_SYNCHRO_ACARS];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t freq_lsb;
    uint8_t freq_msb;
    uint8_t mod;
    uint8_t prekey;
    uint16_t crc;
};
struct tsPid50 {

    uint8_t synchro[SIZE_SYNCHRO_ACARS];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t freq_lsb;
    uint8_t freq_msb;
    uint8_t mod;
    uint8_t prekey;
    uint16_t crc;
};
struct tsPid53 {

    uint8_t synchro[SIZE_SYNCHRO_ACARS];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint8_t err_code;
    uint8_t err_donnees;
    uint16_t crc;
};

struct tsPid25
  {
    uint8_t synchro[SIZE_SYNCHRO_ACARS];
    uint8_t protocoleCode;
    uint8_t pid;
    uint8_t lengthMsb;
    uint8_t lengthLsb;
    uint16_t crc;

  };


namespace Ui {
class udpacars;
}

class udpacars : public QMainWindow
{
    Q_OBJECT

public:
    explicit udpacars(QWidget *parent = nullptr);
    ~udpacars();

private slots:
    void on_SQP_clicked();

    void on_TRANSMISSION_RATIO_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_Clear_clicked();

    void on_actionPARAM_REQ_triggered();
    void on_actionPWR_SET_REQ_triggered();

    void on_actionMODE_SET_REQ_triggered();

    void on_actionPURGE_REQ_triggered();

    void on_actionPARAM_REQ_2_triggered();

    void on_actionMODE_SET_REQ_2_triggered();

    void on_actionUNIT_DATA_REQ_triggered();

    void on_pushButton_2_clicked();

private :

    static const unsigned int SHIFTER;
    static const unsigned short TABLE[];

public:

    unsigned short calculateCRC16(char input[], int lenght);
private:
    Ui::udpacars *ui;
    QUdpSocket *mSocket1;
    QUdpSocket *mSocket2;
    QHostAddress sender;
    quint16 senderPort;
    histogramme histogramme;
    QChartView *graphique; // un widget pour afficher un graphe
    QChart *graphe; // la représentation d'un graphe
    QLineSeries *courbe; // les données
    int numbers[sizeh] {0};
    int counter=0;
    form1 form1;
    version version;
    histoacarsudp histoacarsudp;
};

#endif // UDPACARS_H
