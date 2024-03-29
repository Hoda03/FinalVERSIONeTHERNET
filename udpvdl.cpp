#include "udpvdl.h"
#include "ui_udpvdl.h"
#include <iostream>
#include <QString>
#include <iostream>
#include <QByteArray>
#include <bitset>
/*#include "histogramme.h"
#include "reptransudpvdl.h"
#include "raptrans.h"*/

const uint8_t syncrovdl2[SIZE_SYNCHRO_VDL2] = {0xff,0x00,0xf0,0xca};

#define Err_inconnue_ErreurCode 0
#define Pid_inconnue_ErreurCode 1
#define Data_fausses_ErreurCode 2

#define Not_Sent_ErreurData 0
#define Sent_ErreurData 1
#define EcrasementTamponEmission_ErreurData 2


#define CRC_P       0x8408       /* (x**0)000 0(x**5)00 0000 (x**12)000 */
                                     /* 1     000 01     00 0000 1      000 */
#define CRC_INITFCS16    0x0000  /* Initial FCS value */
#define CRC_GOODFCS16    0x0000  /* Good final FCS value */
#define CRC_SIZE_TABLEAU 256     /* de 0 à 0xFF */

int counter_confvdl = 0;
int counter_indvdl = 0;

udpvdl::udpvdl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::udpvdl)
{
    ui->setupUi(this);
    this->setWindowTitle("MODE2&UDP");
    this->setStyleSheet("QMainWindow { background-color : #ffffff}");

    // Create a UDP Socket
       mSocket = new QUdpSocket(this);
       mSocket->bind(1235,QUdpSocket::ShareAddress);
       mSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 128 * 1024);
       mSocket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 64 * 1024);

       connect(mSocket,&QUdpSocket::readyRead,[&](){


           while (mSocket ->hasPendingDatagrams())
           {

               QByteArray data;
               QHostAddress sender;
               quint16 senderPort;
               data.resize(mSocket->pendingDatagramSize());

               mSocket->readDatagram(data.data(),data.size(),&sender, &senderPort);

               QByteArray ba_as_hex_string = data.toHex();



               if ((data[5] == 80) && (data[8] >= 18)){

                   int PARAM_REQ = ui-> frequence_3 -> value();
                   ui-> plainTextEdit-> appendPlainText(QString("PARAM_CONF = %1").arg(PARAM_REQ));
                   ui->  plainTextEdit_4->appendPlainText(ba_as_hex_string);



               }
               if (((data[8] == 47) || (data[8] == 44) || (data[8] == 40)) && ( data[9] == 1)){

                   int PWR_SET_REQ = ui -> puissance_3 -> value();
                    ui->plainTextEdit->appendPlainText(QString("PWR_SET_CONF = %1").arg(PWR_SET_REQ));
                    ui->  plainTextEdit_4->appendPlainText(ba_as_hex_string);

               }

               if( data[9] == 1 && data[11] == 119){

                      ui->plainTextEdit->appendPlainText(QString("MODE_SET_CONF"));
                      ui->  plainTextEdit_4->appendPlainText(ba_as_hex_string);

                  }
               if(data[5] == 83){


                   ui->plainTextEdit->appendPlainText(QString(" VDR_ERROR IND"));
                   ui->  plainTextEdit_4->appendPlainText(ba_as_hex_string);

               }
               else if( data[5] == 86 ){
                     counter_confvdl++;
                     ui->plainTextEdit->appendPlainText(QString("[%1] : UNIT DATA CONF").arg(counter_confvdl));
                     ui->  plainTextEdit_4->appendPlainText(ba_as_hex_string);
                     uint16_t tab16;
                     tab16 = ( data[9] << 8 ) | data[10] ;
                     int a_as_int =(int) data[8];
                     int a_as_int2 =(int) data[11];
                     int z =(int) tab16;



                     QString s = QString::number(a_as_int);
                     QString g = QString::number(z);
                     QString f = QString::number(a_as_int2 );

                     ui->info->appendPlainText(QString("statut de transmission : %1").arg(s));
                     ui->info->appendPlainText(QString("Mac Delay : %1").arg(g));
                     ui->info->appendPlainText(QString("Tx Pkt sequence No. : %1").arg(f));



                 }
               if( data[5] == 81 ){
                     counter_indvdl++;
                     ui->plainTextEdit->appendPlainText(QString("[%1] : UNIT DATA IND").arg(counter_indvdl));
                     ui->  plainTextEdit_4->appendPlainText(ba_as_hex_string);
                   /*  QByteArray houda;
                     QDataStream s(&houda, QIODevice::WriteOnly);

                     if (false){

                         s.setByteOrder(QDataStream::LittleEndian);
                     }
                     for (int i=10; i < (ui-> donnees_3 -> value()) + 11 ;i++){

                     s << data[i];


                 }*/
                  //   mSocket->writeDatagram(houda,QHostAddress::LocalHost, 5555);


                 }
               else if( data[5] == 84){

                     ui->plainTextEdit->appendPlainText(QString("SQP IND"));
                     ui->  plainTextEdit_4->appendPlainText(ba_as_hex_string);
                     mSocket->writeDatagram(data,QHostAddress::LocalHost, 1478);





                 }

           }
   });

}

uint16_t CRC16(uint8_t *x, uint16_t len) {
    uint8_t *data = x;
    uint16_t crc=0;

    while (len--) {
        crc ^= *data++;
        for (uint8_t k = 0; k < 8; k++)
            if (crc & 1) crc =(crc >> 1) ^ 0x8408;
            else crc = crc >> 1;
    }

    return crc;
}

udpvdl::~udpvdl()
{
    delete ui;
}

void udpvdl::on_pushButton_clicked()
{
    struct tsPid21{
           uint8_t synchro[SIZE_SYNCHRO_VDL2];
           uint8_t protocoleCode;
           uint8_t pid;
           uint8_t lengthMsb;
           uint8_t lengthLsb;
           uint8_t clic;
           uint16_t crc;
           char str1[16384];


       };

       /*la variable counter change à chaque fois on clique sur le button unit data req */
       counter++;

       /*--------------Définition des 16k valeur à pouvoir envoyer sous le protocole VDL 2------------------------*/

            uint16_t value = ui->donnees_3->value()+1;
            uint8_t array[2];
            array[0]=value & 0xff;
            array[1]=(value >> 8);


           char table22[ ui->donnees_3->value() ] ;
           unsigned char table222[ui->donnees_3->value()] ;
             for(int i=0; i< (ui->donnees_3->value()); i++){
               srand((unsigned) time(0));
               int strn =  (rand() % 255);
               unsigned char monsef = (unsigned char) strn;
               table22[i] = strn;

               table222[i] = monsef;

               }

            char str[16384];

            str[16383] = '\0';
            strncpy ( str, table22, value );
            QByteArray databuf = QByteArray(reinterpret_cast<char*>(table22), ui->donnees_3->value());


            /*-------------Définition des champs de la trame et l'intégrer dans un flus d'envoie------------- */

            tsPid21 Pid21;

            Pid21.synchro [0] = syncrovdl2[0];
            Pid21.synchro [1] = syncrovdl2[1];
            Pid21.synchro [2] = syncrovdl2[2];
            Pid21.synchro [3] = syncrovdl2[3];
            Pid21.protocoleCode = 0xF1;
            Pid21.pid = 0x21;
            Pid21.lengthMsb=array[1];
            Pid21.lengthLsb=array[0];
            Pid21.clic=counter;

            /*-------------------------------Calcul du Crc16 Kermit-------------------------------------*/


            unsigned char myData3[] ={0xff ,0x00, 0xf0, 0xca,0xf1, 0x21,array[1],array[0],counter};
            unsigned char allstrings[sizeof(table222)+sizeof(myData3)];
            memcpy(allstrings,myData3,sizeof(myData3));
            memcpy(allstrings+sizeof(myData3),table222,sizeof(table222));
            unsigned short myCrc;
            unsigned int myDataLen = sizeof(table222)+ sizeof(myData3);

            myCrc = CRC16(allstrings, myDataLen);
            myCrc = ((myCrc << 8) | (myCrc >> 8));

            Pid21.crc=myCrc;



        /*-------------------Intégration des champs du buffer dans un flux d'envoie--------------------------*/


        QByteArray buffer;
        //  ecrire les données dans le flux d'envoie
        QDataStream s(&buffer, QIODevice::WriteOnly);

        if (false){

            s.setByteOrder(QDataStream::LittleEndian);
        }
         s << (uint8_t)Pid21.synchro [0]<< (uint8_t)Pid21.synchro [1]<<(uint8_t)Pid21.synchro [2]
           <<(uint8_t)Pid21.synchro [3]  << (uint8_t)Pid21.protocoleCode << (uint8_t)Pid21.pid
           << (uint8_t)Pid21.lengthMsb<< (uint8_t)Pid21.lengthLsb
           << (uint8_t)Pid21.clic ;



           QByteArray buffer3;
           //  ecrire les données dans le flux d'envoie

           QDataStream g(&buffer3, QIODevice::WriteOnly);

           if (false){

               g.setByteOrder(QDataStream::LittleEndian);
           }
           g <<(uint16_t) Pid21.crc;


           QByteArray buffer5 = buffer +databuf + buffer3;


        /*--------------------------------Envoie des données--------------------------------------*/
         /*  for (int i = 9; i<ui-> donnees_3->value();i++){

               QByteArray buffer5 = buffer +databuf + buffer3;


               QByteArray buffern;
               QDataStream s(&buffern, QIODevice::WriteOnly);

               if (false){

                   s.setByteOrder(QDataStream::LittleEndian);
               }
               s << buffer5[i];
                mSocket->writeDatagram(buffern,QHostAddress::LocalHost, 2323);
        }*/


        QString ip = ui->hostaddress1_6->text();                      //Get the other party's ip
        short port = ui->port1_6->value();

        mSocket->writeDatagram(buffer5,QHostAddress(ip), port);
     //   mSocket->writeDatagram(buffer5,QHostAddress::LocalHost, 5555);

        ui->  plainTextEdit_2 -> appendPlainText(QString("[%1] : UINT_DATA_REQ").arg(counter));

        QByteArray ba_as_hex_string = buffer5.toHex();
        ui->  plainTextEdit_3->appendPlainText(ba_as_hex_string);



}


void udpvdl::on_version_clicked()
{
     //version.show();
}


void udpvdl::on_pushButton_3_clicked()
{

}


void udpvdl::on_pushButton_2_clicked()
{
    ui->  plainTextEdit_4->clear();
     ui->  plainTextEdit_3->clear();
     ui->  plainTextEdit_2->clear();
     ui->  plainTextEdit->clear();
     ui->info->clear();

}


void udpvdl::on_actionPARAM_REQ_triggered()
{
    /*-----------------------------------------------------------------------------------*/
      // Algo de traitement de la fréquence
      //Il faut créer une liste qui prend la taille de la valeur de fréquence désiré
      //mettre le nombre saisie dans le tableu sous forme de chiffre

      /*-----------------------------------------------------------------------------------------*/


      int T[6];
      int c = 0;
      int msb[2] , lsb[2] ;
      int monnombre = ui->frequence_3->value();
      int mynumber = 0;
      int p =1 , e = 1 , o = 1;
      /*------------------mettre le nmbre saisie dans un tableau en forme de chiffre---------------------------------*/


      while(monnombre!=0) {
          int mod = monnombre%10;
          T[c] = mod;
          monnombre-=mod;
          monnombre/=10;
          c++;
      }

      /*------------------------Reconversion du tableau en chiffre-----------------------------------------------------*/
     for(int i = 1; i<5 ; i++){
          mynumber =  mynumber + T[i]*p;
          p=p*10;
      }

      msb[0] = T[4] ;
      msb[1] = T[3];

      lsb[0] = T[2];
      lsb[1] = T[1];

      uint8_t var = 0 ;
      for(int k=1;k>=0;k--) {
              var = var +msb[k]*e ; //freq_msb
              e = e*10 ;
      }
      uint8_t var2 = 0 ;
      for(int k=1;k>=0;k--) {
              var2 = var2 +lsb[k]*o ; //freq_lsb
              o = o*10 ;
      }



      uint8_t  var1 = ui -> spinBox_9 -> value();   //Valeur du TIMER1
      uint8_t  var3 = ui -> spinBox_10 -> value();   //Valeur du TIMER2
      uint8_t  var5 = ui->spinBox_12->value();         //Valeur de la persistance

      uint16_t var4 = ui->spinBox_11->value();       //Valeur du compteur
      uint16_t value = var4;
      uint8_t array[2];
      array[0]=value & 0xff;
      array[1]=(value >> 8);

      /*-------------Définition des champs de la trame et son envoie dans un fil------------- */

      if  ( monnombre >= 118000  & monnombre <= 136000 )
              {


                      tsPid20vdl Pid20;
                      Pid20.synchro [0] = syncrovdl2[0];
                      Pid20.synchro [1] = syncrovdl2[1];
                      Pid20.synchro [2] = syncrovdl2[2];
                      Pid20.synchro [3] = syncrovdl2[3];
                      Pid20.mode = 0xF1;
                      Pid20.pid = 0x20;
                      Pid20.dfl1_msb =0x00;
                      Pid20.dfl2_lsb = 0x07;
                      Pid20.freq_msb=var;
                      Pid20.freq_lsb = var2;
                      Pid20.tm1 =var1;
                      Pid20.tm2 =var3;
                      Pid20.M1_lsb= array[0];
                      Pid20.M1_msb= array[1];
                      Pid20.persistance= var5;

                      /*-------------------------------Calcul du Crc16 Kermit-------------------------------------*/

                      unsigned char myData[] = {0xff, 0x00, 0xf0, 0xca, 0xf1, 0x20, 0x00, 0x07,var,var2,var1,var3,array[1], array[0],var5 };
                      unsigned int myDataLen;
                      unsigned short myCrc;
                      myDataLen = sizeof(myData);
                      myCrc = CRC16(myData, myDataLen);
                      myCrc = ((myCrc << 8) | (myCrc >> 8));
                      Pid20.crc=myCrc;


                      /*-------------------Intégration des champs du buffer dans un fil d'envoie--------------------------*/

                      QByteArray buffer;
                      //  ecrire les données dans le flux d'envoie
                      QDataStream s(&buffer, QIODevice::WriteOnly);
                      if (false){

                          s.setByteOrder(QDataStream::LittleEndian);
                      }
                      s << (uint8_t)Pid20.synchro [0]<< (uint8_t)Pid20.synchro [1]<<(uint8_t)Pid20.synchro [2]<<(uint8_t)Pid20.synchro [3]
                        << (uint8_t)Pid20.mode << (uint8_t)Pid20.pid << (uint8_t)Pid20.dfl1_msb <<(uint8_t)Pid20.dfl2_lsb
                        <<(uint8_t)Pid20.freq_msb<<(uint8_t)Pid20.freq_lsb<<(uint8_t)Pid20.tm1<<(uint8_t)Pid20.tm2
                        <<(uint8_t)Pid20.M1_msb<<(uint8_t)Pid20.M1_lsb<<(uint8_t)Pid20.persistance<<(uint16_t)Pid20.crc;

                      /*--------------------------------Envoie des données--------------------------------------*/

                      QString ip = ui->hostaddress1_6->text();                      //Get the other party's ip
                      short port = ui->port1_6->value();

                      mSocket->writeDatagram(buffer,QHostAddress(ip), port);

                      int PARAM_REQ = ui-> frequence_3 -> value();
                      ui-> plainTextEdit_2 -> appendPlainText(QString("PARAM_CONF = %1").arg(PARAM_REQ));

                      QByteArray ba_as_hex_string = buffer.toHex();
                      ui->  plainTextEdit_3->appendPlainText(ba_as_hex_string);



              }

}


void udpvdl::on_actionPWR_SET_REQ_triggered()
{
    /*----------------instruction conditionnelle pour l'envoie de la puissance à la Radio------------------------*/


      int pwr = ui -> puissance_3 -> value();
      uint8_t var3;

     if(  pwr == 50 ) {
           var3 = 47;
      }
     if ( pwr == 25){
           var3 = 44;
      }
     if ( pwr == 10) {

           var3 = 40;
      }

     /*-------------Définition des champs de la trame ------------- */


      tsPidF1vdl PidF1;

      PidF1.synchro [0] = syncrovdl2[0];
      PidF1.synchro [1] = syncrovdl2[1];
      PidF1.synchro [2] = syncrovdl2[2];
      PidF1.synchro [3] = syncrovdl2[3];
      PidF1.protocoleCode = 0xF1;
      PidF1.pid=0xF1;
      PidF1.lengthMsb = 0x00;
      PidF1.lengthLsb = 0x02;
      PidF1.pwr=var3;
      PidF1.req=0;

      /*-------------------------------Calcul du Crc16 Kermit-------------------------------------*/

      unsigned char myData[] = {0xff, 0x00, 0xf0, 0xca, 0xf1, 0xf1,0x00,0x02,var3,0x00};
      unsigned int myDataLen;
      unsigned short myCrc;
      myDataLen = sizeof(myData);
      myCrc = CRC16(myData, myDataLen);
      myCrc = ((myCrc << 8) | (myCrc >> 8));
      PidF1.crc=myCrc ;

      /*-------------------Intégration des champs du buffer dans un fil d'envoie--------------------------*/

      QByteArray buffer;
      QDataStream s(&buffer, QIODevice::WriteOnly);

      if (false){

          s.setByteOrder(QDataStream::LittleEndian);
      }
         s << (uint8_t)PidF1.synchro [0]<< (uint8_t)PidF1.synchro [1]<<(uint8_t)PidF1.synchro [2]
           <<(uint8_t)PidF1.synchro [3]  << (uint8_t)PidF1.protocoleCode << (uint8_t)PidF1.pid
           << (uint8_t)PidF1.lengthMsb <<(uint8_t)PidF1.lengthLsb<<(uint8_t)PidF1.pwr
           <<(uint8_t)PidF1.req<<(uint16_t)PidF1.crc;


         /*--------------------------------Envoie des données--------------------------------------*/

       QString ip = ui->hostaddress1_6->text();                      //Get the other party's ip
       short port = ui->port1_6->value();

       mSocket->writeDatagram(buffer,QHostAddress(ip), port);
       int PWR_SET_REQ = ui -> puissance_3 -> value();
       ui->  plainTextEdit_2 -> appendPlainText(QString("PWR_SET_REQ = %1").arg(PWR_SET_REQ));

       QByteArray ba_as_hex_string = buffer.toHex();
       ui->  plainTextEdit_3->appendPlainText(ba_as_hex_string);


}



void udpvdl::on_actionMODE_SET_REQ_triggered()
{
    /*-------------Définition des champs de la trame ------------- */

       tsPidF0vdl PidF0;
       PidF0.synchro [0] = syncrovdl2[0];
       PidF0.synchro [1] = syncrovdl2[1];
       PidF0.synchro [2] = syncrovdl2[2];
       PidF0.synchro [3] = syncrovdl2[3];
       PidF0.protocoleCode = 0xF1;
       PidF0.pid=0xF0;
       PidF0.lengthMsb = 0x00;
       PidF0.lengthLsb = 0x02;
       PidF0.mode=0xF2;
       PidF0.req=0;

       /*-------------------------------Calcul du Crc16 Kermit-------------------------------------*/


       unsigned char myData[] = {0xff, 0x00, 0xf0, 0xca, 0xf1, 0xf0,0x00,0x02,0xf2,0x00};
       unsigned int myDataLen;
       unsigned short myCrc;
       myDataLen = sizeof(myData);
       myCrc = CRC16(myData, myDataLen);
       myCrc = ((myCrc << 8) | (myCrc >> 8));
       PidF0.crc= myCrc;

       /*-------------------Intégration des champs du buffer dans un fil d'envoie--------------------------*/

       QByteArray buffer;

       //  ecrire les données dans le flux d'envoie
       QDataStream s(&buffer, QIODevice::WriteOnly);

       if (false){

           s.setByteOrder(QDataStream::LittleEndian);

       }
       s  << (uint8_t)PidF0.synchro [0]<< (uint8_t)PidF0.synchro [1]<<(uint8_t)PidF0.synchro [2]
          <<(uint8_t)PidF0.synchro [3]  << (uint8_t)PidF0.protocoleCode << (uint8_t)PidF0.pid
          << (uint8_t)PidF0.lengthMsb<< (uint8_t)PidF0.lengthLsb<< (uint8_t)PidF0.mode
          << (uint8_t)PidF0.req   << (uint16_t)PidF0.crc  ;

       /*--------------------------------Envoie des données--------------------------------------*/


       QString ip = ui->hostaddress1_6->text();                      //Get the other party's ip
       short port = ui->port1_6->value();
       mSocket->writeDatagram(buffer,QHostAddress(ip), port);
       ui->  plainTextEdit_2 -> appendPlainText("MODE_SET_REQ");

       QByteArray ba_as_hex_string = buffer.toHex();
       ui->  plainTextEdit_3->appendPlainText(ba_as_hex_string);


}


void udpvdl::on_actionPARAM_REQ_2_triggered()
{
    /*-----------------------------------------------------------------------------------*/
      // Algo de traitement de la fréquence
      //Il faut créer une liste qui prend la taille de la valeur de fréquence désiré
      //mettre le nombre saisie dans le tableu sous forme de chiffre

      /*-----------------------------------------------------------------------------------------*/


      int T[6];
      int c = 0;
      int msb[2] , lsb[2] ;
      int monnombre = ui->frequence_3->value();
      int mynumber = 0;
      int p =1 , e = 1 , o = 1;
      /*------------------mettre le nmbre saisie dans un tableau en forme de chiffre---------------------------------*/


      while(monnombre!=0) {
          int mod = monnombre%10;
          T[c] = mod;
          monnombre-=mod;
          monnombre/=10;
          c++;
      }

      /*------------------------Reconversion du tableau en chiffre-----------------------------------------------------*/
     for(int i = 1; i<5 ; i++){
          mynumber =  mynumber + T[i]*p;
          p=p*10;
      }

      msb[0] = T[4] ;
      msb[1] = T[3];

      lsb[0] = T[2];
      lsb[1] = T[1];

      uint8_t var = 0 ;
      for(int k=1;k>=0;k--) {
              var = var +msb[k]*e ; //freq_msb
              e = e*10 ;
      }
      uint8_t var2 = 0 ;
      for(int k=1;k>=0;k--) {
              var2 = var2 +lsb[k]*o ; //freq_lsb
              o = o*10 ;
      }



      uint8_t  var1 = ui -> spinBox_9 -> value();   //Valeur du TIMER1
      uint8_t  var3 = ui -> spinBox_10 -> value();   //Valeur du TIMER2
      uint8_t  var5 = ui->spinBox_12->value();         //Valeur de la persistance

      uint16_t var4 = ui->spinBox_11->value();       //Valeur du compteur
      uint16_t value = var4;
      uint8_t array[2];
      array[0]=value & 0xff;
      array[1]=(value >> 8);

      /*-------------Définition des champs de la trame et son envoie dans un fil------------- */

      if  ( ui -> frequence_3 -> value() >= 118000  &  ui -> frequence_3 -> value() <= 136000 )
              {


                      tsPid20vdl Pid20;
                      Pid20.synchro [0] = syncrovdl2[0];
                      Pid20.synchro [1] = syncrovdl2[1];
                      Pid20.synchro [2] = syncrovdl2[2];
                      Pid20.synchro [3] = syncrovdl2[3];
                      Pid20.mode = 0xF1;
                      Pid20.pid = 0x20;
                      Pid20.dfl1_msb =0x00;
                      Pid20.dfl2_lsb = 0x07;
                      Pid20.freq_msb=var;
                      Pid20.freq_lsb = var2;
                      Pid20.tm1 =var1;
                      Pid20.tm2 =var3;
                      Pid20.M1_lsb= array[0];
                      Pid20.M1_msb= array[1];
                      Pid20.persistance= var5;

                      /*-------------------------------Calcul du Crc16 Kermit-------------------------------------*/

                      unsigned char myData[] = {0xff, 0x00, 0xf0, 0xca, 0xf1, 0x20, 0x00, 0x07,var,var2,var1,var3,array[1], array[0],var5 };
                      unsigned int myDataLen;
                      unsigned short myCrc;
                      myDataLen = sizeof(myData);
                      myCrc = CRC16(myData, myDataLen);
                      myCrc = ((myCrc << 8) | (myCrc >> 8));
                      Pid20.crc=myCrc;


                      /*-------------------Intégration des champs du buffer dans un fil d'envoie--------------------------*/

                      QByteArray buffer;
                      //  ecrire les données dans le flux d'envoie
                      QDataStream s(&buffer, QIODevice::WriteOnly);
                      if (false){

                          s.setByteOrder(QDataStream::LittleEndian);
                      }
                      s << (uint8_t)Pid20.synchro [0]<< (uint8_t)Pid20.synchro [1]<<(uint8_t)Pid20.synchro [2]<<(uint8_t)Pid20.synchro [3]
                        << (uint8_t)Pid20.mode << (uint8_t)Pid20.pid << (uint8_t)Pid20.dfl1_msb <<(uint8_t)Pid20.dfl2_lsb
                        <<(uint8_t)Pid20.freq_msb<<(uint8_t)Pid20.freq_lsb<<(uint8_t)Pid20.tm1<<(uint8_t)Pid20.tm2
                        <<(uint8_t)Pid20.M1_msb<<(uint8_t)Pid20.M1_lsb<<(uint8_t)Pid20.persistance<<(uint16_t)Pid20.crc;

                      /*--------------------------------Envoie des données--------------------------------------*/

                      QString ip = ui->hostaddress1_5->text();                      //Get the other party's ip
                      short port = ui->port1_5->value();

                      mSocket->writeDatagram(buffer,QHostAddress(ip), port);
                      int PARAM_REQ = ui-> frequence_3 -> value();
                      ui-> plainTextEdit_2 -> appendPlainText(QString("PARAM_CONF = %1").arg(PARAM_REQ));

                      QByteArray ba_as_hex_string = buffer.toHex();
                      ui->  plainTextEdit_3->appendPlainText(ba_as_hex_string);



              }

}


void udpvdl::on_actionMODE_SET_REQ_2_triggered()
{
    /*-------------Définition des champs de la trame ------------- */

       tsPidF0vdl PidF0;
       PidF0.synchro [0] = syncrovdl2[0];
       PidF0.synchro [1] = syncrovdl2[1];
       PidF0.synchro [2] = syncrovdl2[2];
       PidF0.synchro [3] = syncrovdl2[3];
       PidF0.protocoleCode = 0xF1;
       PidF0.pid=0xF0;
       PidF0.lengthMsb = 0x00;
       PidF0.lengthLsb = 0x02;
       PidF0.mode=0xF2;
       PidF0.req=0;

       /*-------------------------------Calcul du Crc16 Kermit-------------------------------------*/


       unsigned char myData[] = {0xff, 0x00, 0xf0, 0xca, 0xf1, 0xf0,0x00,0x02,0xf2,0x00};
       unsigned int myDataLen;
       unsigned short myCrc;
       myDataLen = sizeof(myData);
       myCrc = CRC16(myData, myDataLen);
       myCrc = ((myCrc << 8) | (myCrc >> 8));
       PidF0.crc= myCrc;

       /*-------------------Intégration des champs du buffer dans un fil d'envoie--------------------------*/

       QByteArray buffer;

       //  ecrire les données dans le flux d'envoie
       QDataStream s(&buffer, QIODevice::WriteOnly);

       if (false){

           s.setByteOrder(QDataStream::LittleEndian);

       }
       s  << (uint8_t)PidF0.synchro [0]<< (uint8_t)PidF0.synchro [1]<<(uint8_t)PidF0.synchro [2]
          <<(uint8_t)PidF0.synchro [3]  << (uint8_t)PidF0.protocoleCode << (uint8_t)PidF0.pid
          << (uint8_t)PidF0.lengthMsb<< (uint8_t)PidF0.lengthLsb<< (uint8_t)PidF0.mode
          << (uint8_t)PidF0.req   << (uint16_t)PidF0.crc  ;

       /*--------------------------------Envoie des données--------------------------------------*/


       QString ip = ui->hostaddress1_5->text();                      //Get the other party's ip
       short port = ui->port1_5->value();
       mSocket->writeDatagram(buffer,QHostAddress(ip), port);
       ui->  plainTextEdit_2 -> appendPlainText("MODE_SET_REQ");

       QByteArray ba_as_hex_string = buffer.toHex();
       ui->  plainTextEdit_3->appendPlainText(ba_as_hex_string);



}


void udpvdl::on_actionPURGE_REQ_triggered()
{
    /*-------------Définition des champs de la trame ------------- */


       tsPid010bvdl Pid010b;

       Pid010b.synchro [0] = syncrovdl2[0];
       Pid010b.synchro [1] = syncrovdl2[1];
       Pid010b.synchro [2] = syncrovdl2[2];
       Pid010b.synchro [3] = syncrovdl2[3];
       Pid010b.protocoelCode=0x14;
       Pid010b.pid=0x1F;
       Pid010b.donnees=0x00;
       Pid010b.sal=0x00;

       /*-------------------------------Calcul du Crc16 Kermit-------------------------------------*/

       unsigned char myData[] = {0xff, 0x00, 0xf0, 0xca, 0x14, 0x1f,0x00,0x00};
       unsigned int myDataLen;
       unsigned short myCrc;
       myDataLen = sizeof(myData);
       myCrc = CRC16(myData, myDataLen);
       myCrc = ((myCrc << 8) | (myCrc >> 8));
       Pid010b.crc=myCrc;

       /*-------------------Intégration des champs du buffer dans un flux d'envoie--------------------------*/


       QByteArray buffer;
       //  ecrire les données dans le flux d'envoie
       QDataStream s(&buffer, QIODevice::WriteOnly);

       if (false){

           s.setByteOrder(QDataStream::LittleEndian);

       }
       s  << (uint8_t)Pid010b.synchro [0]<< (uint8_t)Pid010b.synchro [1]<<(uint8_t)Pid010b.synchro [2]
          <<(uint8_t)Pid010b.synchro [3]<<(uint8_t)Pid010b.protocoelCode<<(uint8_t)Pid010b.pid
          <<(uint8_t)Pid010b.donnees<<(uint8_t)Pid010b.sal<<(uint16_t)Pid010b.crc;


       /*--------------------------------Envoie des données--------------------------------------*/

       QString ip = ui->hostaddress1_6->text();                      //Get the other party's ip
       short port = ui->port1_6->value();
       mSocket->writeDatagram(buffer,QHostAddress(ip), port);
       ui->  plainTextEdit_2 -> appendPlainText("PURGE_REQ");

       QByteArray ba_as_hex_string = buffer.toHex();
       ui->  plainTextEdit_3->appendPlainText(ba_as_hex_string);
}


void udpvdl::on_sqp_clicked()
{

  //  histogramme.show();
}






void udpvdl::on_transmission_ratio_clicked()
{
    form.show();

}


void udpvdl::on_pushButton_4_clicked()
{
  int val = ui->n_data->value();
  for(int i =0; i< val+1; i++){
      struct tsPid21{
             uint8_t synchro[SIZE_SYNCHRO_VDL2];
             uint8_t protocoleCode;
             uint8_t pid;
             uint8_t lengthMsb;
             uint8_t lengthLsb;
             uint8_t clic;
             uint16_t crc;
             char str1[16384];


         };

         /*la variable counter change à chaque fois on clique sur le button unit data req */
         counter1++;

         /*--------------Définition des 16k valeur à pouvoir envoyer sous le protocole VDL 2------------------------*/

              uint16_t value = ui->donnees_3->value()+1;
              uint8_t array[2];
              array[0]=value & 0xff;
              array[1]=(value >> 8);
             char table22[ ui->donnees_3->value() ] ;
             unsigned char table222[ui->donnees_3->value()] ;
               for(int i=0; i< (ui->donnees_3->value()); i++){
                 srand((unsigned) time(0));
                 int strn =  (rand() % 255);
                 unsigned char monsef = (unsigned char) strn;
                 table22[i] = strn;

                 table222[i] = monsef;

                 }

              char str[16384];

              str[16383] = '\0';
              strncpy ( str, table22, value );
              QByteArray databuf = QByteArray(reinterpret_cast<char*>(table22), ui->donnees_3->value());


              /*-------------Définition des champs de la trame et l'intégrer dans un flus d'envoie------------- */

              tsPid21 Pid21;

              Pid21.synchro [0] = syncrovdl2[0];
              Pid21.synchro [1] = syncrovdl2[1];
              Pid21.synchro [2] = syncrovdl2[2];
              Pid21.synchro [3] = syncrovdl2[3];
              Pid21.protocoleCode = 0xF1;
              Pid21.pid = 0x21;
              Pid21.lengthMsb=array[1];
              Pid21.lengthLsb=array[0];
              Pid21.clic=counter;

              /*-------------------------------Calcul du Crc16 Kermit-------------------------------------*/


              unsigned char myData3[] ={0xff ,0x00, 0xf0, 0xca,0xf1, 0x21,array[1],array[0],counter};
              unsigned char allstrings[sizeof(table222)+sizeof(myData3)];
              memcpy(allstrings,myData3,sizeof(myData3));
              memcpy(allstrings+sizeof(myData3),table222,sizeof(table222));
              unsigned short myCrc;
              unsigned int myDataLen = sizeof(table222)+ sizeof(myData3);

              myCrc = CRC16(allstrings, myDataLen);
              myCrc = ((myCrc << 8) | (myCrc >> 8));

              Pid21.crc=myCrc;



          /*-------------------Intégration des champs du buffer dans un flux d'envoie--------------------------*/


          QByteArray buffer;
          //  ecrire les données dans le flux d'envoie
          QDataStream s(&buffer, QIODevice::WriteOnly);

          if (false){

              s.setByteOrder(QDataStream::LittleEndian);
          }
           s << (uint8_t)Pid21.synchro [0]<< (uint8_t)Pid21.synchro [1]<<(uint8_t)Pid21.synchro [2]
             <<(uint8_t)Pid21.synchro [3]  << (uint8_t)Pid21.protocoleCode << (uint8_t)Pid21.pid
             << (uint8_t)Pid21.lengthMsb<< (uint8_t)Pid21.lengthLsb
             << (uint8_t)Pid21.clic ;



             QByteArray buffer3;
             //  ecrire les données dans le flux d'envoie

             QDataStream g(&buffer3, QIODevice::WriteOnly);

             if (false){

                 g.setByteOrder(QDataStream::LittleEndian);
             }
             g <<(uint16_t) Pid21.crc;


             QByteArray buffer5 = buffer +databuf + buffer3;


          /*--------------------------------Envoie des données--------------------------------------*/
           /*  for (int i = 9; i<ui-> donnees_3->value();i++){

                 QByteArray buffer5 = buffer +databuf + buffer3;


                 QByteArray buffern;
                 QDataStream s(&buffern, QIODevice::WriteOnly);

                 if (false){

                     s.setByteOrder(QDataStream::LittleEndian);
                 }
                 s << buffer5[i];
                  mSocket->writeDatagram(buffern,QHostAddress::LocalHost, 2323);
          }*/


          QString ip = ui->hostaddress1_6->text();                      //Get the other party's ip
          short port = ui->port1_6->value();

          mSocket->writeDatagram(buffer5,QHostAddress(ip), port);
          mSocket->writeDatagram(buffer5,QHostAddress::LocalHost, 5555);

          ui->  plainTextEdit_2 -> appendPlainText("UINT_DATA_REQ");

          QByteArray ba_as_hex_string = buffer5.toHex();
          ui->  plainTextEdit_3->appendPlainText(ba_as_hex_string);


  }
}

