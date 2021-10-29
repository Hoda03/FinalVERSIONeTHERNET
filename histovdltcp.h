#ifndef HISTOVDLTCP_H
#define HISTOVDLTCP_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCharts>
#include <QHostAddress>
#include <QUdpSocket>
constexpr size_t sizet =100;

namespace Ui {
class histovdltcp;
}

class histovdltcp : public QMainWindow
{
    Q_OBJECT

public:
    explicit histovdltcp(QWidget *parent = nullptr);
    ~histovdltcp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::histovdltcp *ui;
    QUdpSocket *mSockett;
    QHostAddress sender;
    quint16 senderPort;
    QChartView *graphique; // un widget pour afficher un graphe
    QChart *graphe; // la représentation d'un graphe
    QLineSeries *courbe; // les données
    int numbers[sizet] {0};
    int counter=0;
};

#endif // HISTOVDLTCP_H
