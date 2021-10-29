#include "form1.h"
#include "ui_form1.h"


constexpr size_t sizer =255;
int bff11[sizer] {0};
int bff21[sizer] {0};
bool isBff1End1 {false};
bool isBff2End1 {false};

int counter11 =0;
int counter21 =0;
int counter_31 =0;


form1::form1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form1)
{
    ui->setupUi(this);
    mSocketF = new QUdpSocket(this);
    mSocketF->bind(QHostAddress::LocalHost,6666);
    this->setWindowTitle("Bit Error Rate Test");
    this->setStyleSheet("QMainWindow { background-color : #ffffff}");
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

    connect(mSocketF,&QUdpSocket::readyRead,[&](){
        while (mSocketF ->hasPendingDatagrams())
        {


            QByteArray data;
            QHostAddress sender;
            quint16 senderPort;
            data.resize(mSocketF->pendingDatagramSize());
            mSocketF->readDatagram(data.data(),data.size(),&sender, &senderPort);



            if (data[5] == 33 ){
                    counter11++ ;
                    ui->label_6->setNum(counter11);

                   int longueur = data.size() -2;
                   for(int i = 8; i< longueur ; i++)
                       {
                           int bff = (int) data[i];
                           QString result = QString::number( bff, 16 );
                           ui->  plainTextEdit->appendPlainText(QString("[%1] : ").arg(i-8) + result);

                       }
                   ui->  plainTextEdit->appendPlainText(QString("----------End Bloc-----------"));

            }
            if (data[0] == 1){
                counter21++ ;
                ui->label_8->setNum(counter21);

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
                       bff11[z-8] = (int) data[z];

                   }
                   isBff1End1 = true;
                }
            if (data[0] == 1){

                    int longueur = data.size();
                    for(int i = 0; i< longueur ; i++){
                        bff21[i] = (int) data[i];
                    }
                    isBff2End1 = true;
                }

                if (isBff1End1 && isBff2End1)
                {
                 int longueur = data.size();
                 for(int n=0; n< longueur; n++) {

                    if((int) bff21[n] == (int) bff11[n]){
                        ui->label_4->setNum(0);

                    }
                    else {
                        counter_31++;
                        ui->label_4->setNum(counter_31);
                        ui->  plainTextEdit_3->appendPlainText(QString("[%1]  ").arg(n) );

                    }
                }
                }
        }});}

form1::~form1()
{
    delete ui;
}
