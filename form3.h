#ifndef FORM3_H
#define FORM3_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>

namespace Ui {
class form3;
}

class form3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit form3(QWidget *parent = nullptr);
    ~form3();

private:
    Ui::form3 *ui;
    QHostAddress sender;
    quint16 senderPort;
    QUdpSocket *mSocketW;
};

#endif // FORM3_H
