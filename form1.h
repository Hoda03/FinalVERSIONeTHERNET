#ifndef FORM1_H
#define FORM1_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>

namespace Ui {
class form1;
}

class form1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit form1(QWidget *parent = nullptr);
    ~form1();

private:
    Ui::form1 *ui;
    QHostAddress sender;
    quint16 senderPort;
    QUdpSocket *mSocketF;
};

#endif // FORM1_H
