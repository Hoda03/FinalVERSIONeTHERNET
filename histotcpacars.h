#ifndef HISTOTCPACARS_H
#define HISTOTCPACARS_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCharts>
#include <QHostAddress>
#include <QUdpSocket>

constexpr size_t sizez =100;

namespace Ui {
class histotcpacars;
}

class histotcpacars : public QMainWindow
{
    Q_OBJECT

public:
    explicit histotcpacars(QWidget *parent = nullptr);
    ~histotcpacars();

private:
    Ui::histotcpacars *ui;
    QUdpSocket *mSocketz;

    QHostAddress sender;
    quint16 senderPort;
    QChartView *graphique; // un widget pour afficher un graphe
    QChart *graphe; // la reprÃ©sentation d'un graphe
    QLineSeries *courbe; // les donnÃ©es
    int numbers[sizez] {0};
    int counter=0;

};

#endif // HISTOTCPACARS_H
