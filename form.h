#ifndef FORM_H
#define FORM_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>

namespace Ui {
class form;
}

class form : public QMainWindow
{
    Q_OBJECT

public:
    explicit form(QWidget *parent = nullptr);
    ~form();

private:
    Ui::form *ui;
    QHostAddress sender;
    quint16 senderPort;
    QUdpSocket *mSocketJ;
};

#endif // FORM_H
