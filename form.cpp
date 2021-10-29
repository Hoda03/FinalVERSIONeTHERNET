#include "form.h"
#include "ui_form.h"
constexpr size_t sizer =255;
int bff1[sizer] {0};
int bff2[sizer] {0};
bool isBff1End {false};
bool isBff2End {false};

#include <QMainWindow>
#include <QWidget>
#include <QUdpSocket>
int counter1 =0;
int counter2 =0;
int counter3 =0;
form::form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form)
{
    ui->setupUi(this);
    this->setWindowTitle("Bit Error Rate Test");
    this->setStyleSheet("QMainWindow { background-color : #ffffff}");

    mSocketJ = new QUdpSocket(this);
    mSocketJ->bind(QHostAddress::LocalHost,5555);
    ui->label_3->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_3->setLineWidth(3);
    ui-> label_3->setMidLineWidth(3);

    ui->label_5->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_5->setLineWidth(3);
    ui-> label_5->setMidLineWidth(3);

    ui->label_7->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_7->setLineWidth(3);
    ui-> label_7->setMidLineWidth(3);

    ui->label_4->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_4->setLineWidth(3);
    ui-> label_4->setMidLineWidth(3);

    ui->label_8->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_8->setLineWidth(3);
    ui-> label_8->setMidLineWidth(3);

    ui->label_6->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_6->setLineWidth(3);
    ui-> label_6->setMidLineWidth(3);


    ui->label_4->setNum(0);
    ui->label_8->setNum(0);
    ui->label_6->setNum(0);

    connect(mSocketJ,&QUdpSocket::readyRead,[&](){
        while (mSocketJ ->hasPendingDatagrams())
        {


            QByteArray data;
            QHostAddress sender;
            quint16 senderPort;
            data.resize(mSocketJ->pendingDatagramSize());
            mSocketJ->readDatagram(data.data(),data.size(),&sender, &senderPort);



            if (data[5] == 33 ){
                    counter1++ ;
                    ui->label_6->setNum(counter1);

                   int longueur = data.size() - 2;
                   for(int i = 9; i< longueur ; i++)
                       {
                           int bff = (int) data[i];
                           QString result = QString::number( bff, 16 );
                           ui->  plainTextEdit->appendPlainText(QString("[%1] : ").arg(i-8) + result);

                       }
                   ui->  plainTextEdit->appendPlainText(QString("----------End Bloc-----------"));

            }
            if (data[0] == 1){
                counter2++ ;
                ui->label_8->setNum(counter2);

                int longueur = data.size();
                for(int i = 0; i< longueur ; i++)
                    {
                        int bff = (int) data[i];
                        QString result = QString::number( bff, 16 );
                        ui->  plainTextEdit_2->appendPlainText(QString("[%1] : ").arg(i) + result);
                    }
                ui->  plainTextEdit_2->appendPlainText(QString("----------End Bloc-----------"));


            }
            if (data[5] == 33 ){
                   int longueur = data.size() -2;
                   for(int z = 8; z< longueur ; z++){
                       bff1[z-8] = (int) data[z];

                   }
                   isBff1End = true;
                }
                if (data[0] == 1){

                    int longueur = data.size();
                    for(int i = 0; i< longueur ; i++){
                        bff2[i] = (int) data[i];
                    }
                    isBff2End = true;
                }

                if (isBff1End && isBff2End)
                {
                 int longueur = data.size();
                 for(int n=0; n< longueur; n++) {

                    if((int) bff2[n] == (int) bff1[n]){
                        ui->label_4->setNum(0);

                    }
                    else {
                        counter3++;
                        ui->label_4->setNum(counter3);
                        ui->  plainTextEdit_3->appendPlainText(QString("[%1]  ").arg(n) );

                    }
                }
                }
        }});
}

form::~form()
{
    delete ui;
}
