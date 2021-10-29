#include "form2.h"
#include "ui_form2.h"


int counter_1 = 0;
int counter_2 = 0;
int counter_3 = 0;

bool isBff1End_1 {false};
bool isBff2End_2 {false};

constexpr size_t sizer =255;
int bff_1[sizer] {0};
int bff_2[sizer] {0};

form2::form2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form2)
{
    ui->setupUi(this);
    mSocketL = new QUdpSocket(this);
    mSocketL->bind(QHostAddress::LocalHost,1111);
    this->setWindowTitle("Bit Error Rate Test");
    this->setStyleSheet("QWidget { background-color : #ffffff}");
    ui->label_3v->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_3v->setLineWidth(3);
    ui-> label_3v->setMidLineWidth(3);

    ui->label_5v->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_5v->setLineWidth(3);
    ui-> label_5v->setMidLineWidth(3);

    ui->label_7v->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_7v->setLineWidth(3);
    ui-> label_7v->setMidLineWidth(3);

    ui->label_4v->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_4v->setLineWidth(3);
    ui-> label_4v->setMidLineWidth(3);

    ui->label_8v->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_8v->setLineWidth(3);
    ui-> label_8v->setMidLineWidth(3);

    ui->label_6v->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    ui-> label_6v->setLineWidth(3);
    ui-> label_6v->setMidLineWidth(3);

    ui->label_4v->setNum(0);
    ui->label_8v->setNum(0);
    ui->label_6v->setNum(0);


    connect(mSocketL,&QUdpSocket::readyRead,[&](){
        while (mSocketL ->hasPendingDatagrams())
        {


            QByteArray data;
            QHostAddress sender;
            quint16 senderPort;
            data.resize(mSocketL->pendingDatagramSize());
            mSocketL->readDatagram(data.data(),data.size(),&sender, &senderPort);

            if (data[5] == 33 ){
                    counter_1++ ;
                    ui->label_6v->setNum(counter_1);

                   int longueur = data.size() -2;
                   for(int i = 8; i< longueur ; i++)
                       {
                           int bff = (int) data[i];
                           QString result = QString::number( bff, 16 );
                           ui->  plainTextEditv->appendPlainText(QString("[%1] : ").arg(i-8) + result);

                       }
                   ui->  plainTextEditv->appendPlainText(QString("----------End Bloc-----------"));

            }
            if (data[0] == 1){
                counter_2++ ;
                ui->label_8v->setNum(counter_2);

                int longueur = data.size() ;
                for(int i = 0; i< longueur ; i++)
                    {
                        int bff = (int) data[i];
                        QString result = QString::number( bff, 16 );
                        ui->  plainTextEdit_2v->appendPlainText(QString("[%1] : ").arg(i) + result);
                    }
                ui->  plainTextEdit_2v->appendPlainText(QString("----------End Bloc-----------"));


            }
            if (data[5] == 33 ){
                   int longueur = data.size() -2;
                   for(int z = 8; z< longueur ; z++){
                       bff_1[z-8] = (int) data[z];

                   }
                   isBff1End_1 = true;
                }
                if (data[0] == 1){

                    int longueur = data.size();
                    for(int i = 0; i< longueur ; i++){
                        bff_2[i] = (int) data[i];
                    }
                    isBff2End_2 = true;
                }

                if (isBff1End_1 && isBff2End_2)
                {
                 int longueur = data.size();
                 for(int n=0; n< longueur; n++) {

                    if((int) bff_2[n] == (int) bff_1[n]){
                        ui->label_4v->setNum(0);

                    }
                    else {
                        counter_3++;
                        ui->label_4v->setNum(counter_3);
                        ui->  plainTextEdit_3v->appendPlainText(QString("[%1]  ").arg(n) );

                    }
                }
                }

        }
   });}

form2::~form2()
{
    delete ui;
}
