#include "form3.h"
#include "ui_form3.h"
int counter_123 = 0;

form3::form3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form3)
{
    ui->setupUi(this);
    mSocketW = new QUdpSocket(this);
    mSocketW->bind(QHostAddress::LocalHost,1964);
    this->setWindowTitle("Bit Error Rate Test");
    this->setStyleSheet("QWidget { background-color : #ffffff}");

    ui->label_3v1->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_3v1->setLineWidth(3);
    ui-> label_3v1->setMidLineWidth(3);

    ui->label_5v1->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_5v1->setLineWidth(3);
    ui-> label_5v1->setMidLineWidth(3);

    ui->label_7v1->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_7v1->setLineWidth(3);
    ui-> label_7v1->setMidLineWidth(3);

    ui->label_4v1->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_4v1->setLineWidth(3);
    ui-> label_4v1->setMidLineWidth(3);

    ui->label_8v1->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_8v1->setLineWidth(3);
    ui-> label_8v1->setMidLineWidth(3);

    ui->label_6v1->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_6v1->setLineWidth(3);
    ui-> label_6v1->setMidLineWidth(3);


    ui->label_4v1->setNum(0);
    ui->label_8v1->setNum(0);
    ui->label_6v1->setNum(0);
    connect(mSocketW,&QUdpSocket::readyRead,[&](){
        while (mSocketW ->hasPendingDatagrams())
        {


            QByteArray data;
            QHostAddress sender;
            quint16 senderPort;
            data.resize(mSocketW->pendingDatagramSize());
            mSocketW->readDatagram(data.data(),data.size(),&sender, &senderPort);
            if (data[5] == 33 ){
                                counter_123++ ;
                                ui->label_6v1->setNum(counter_123);

                               int longueur = data.size() -2;
                               for(int i = 9; i< longueur ; i++)
                                   {
                                       int bff = (int) data[i];
                                       QString result = QString::number( bff, 16 );
                                       ui->  plainTextEditv1->appendPlainText(QString("[%1] : ").arg(i-8) + result);

                                   }
                               ui->  plainTextEditv1->appendPlainText(QString("----------End Bloc-----------"));

                        }

    }});}

form3::~form3()
{
    delete ui;
}
