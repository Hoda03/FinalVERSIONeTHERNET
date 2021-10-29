#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCharts>
#include <QHostAddress>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class histogramme; }
QT_END_NAMESPACE
constexpr size_t sizen =100;

namespace Ui {
class histogramme;
}

class histogramme : public QMainWindow
{
    Q_OBJECT

public:
    explicit histogramme(QWidget *parent = nullptr);
    ~histogramme();

private:
    Ui::histogramme *ui;
    QUdpSocket *mSocketh;

    QHostAddress sender;
    quint16 senderPort;
    QChartView *graphique; // un widget pour afficher un graphe
    QChart *graphe; // la représentation d'un graphe
    QLineSeries *courbe; // les données

private:
    int numbers[sizen] {0};
    int counter=0;
};

#endif // HISTOGRAMME_H
