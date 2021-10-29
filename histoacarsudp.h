#ifndef HISTOACARSUDP_H
#define HISTOACARSUDP_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCharts>
#include <QHostAddress>
#include <QUdpSocket>

constexpr size_t sizex =100;

namespace Ui {
class histoacarsudp;
}

class histoacarsudp : public QMainWindow
{
    Q_OBJECT

public:
    explicit histoacarsudp(QWidget *parent = nullptr);
    ~histoacarsudp();

private:
    Ui::histoacarsudp *ui;
    QUdpSocket *mSocketx;

    QHostAddress sender;
    quint16 senderPort;
    QChartView *graphique; // un widget pour afficher un graphe
    QChart *graphe; // la reprÃ©sentation d'un graphe
    QLineSeries *courbe; // les donnÃ©es
    int numbers[sizex] {0};
    int counter=0;

};

#endif // HISTOACARSUDP_H
