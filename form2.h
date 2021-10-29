#ifndef FORM2_H
#define FORM2_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
namespace Ui {
class form2;
}

class form2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit form2(QWidget *parent = nullptr);
    ~form2();

private:
    Ui::form2 *ui;
    QHostAddress sender;
    quint16 senderPort;
    QUdpSocket *mSocketL;
};

#endif // FORM2_H
