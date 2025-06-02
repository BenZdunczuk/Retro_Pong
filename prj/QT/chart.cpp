#include "chart.h"
#include <QPainter>
#include <QtMath>
#include <QTimer>

/**
* \file
* \brief Definicja metody klasy chart
*
* Zawiera definicję metod klasy chart, używanej do rysowania wykresów ilustrujących dane z sensorów.
*/

    /**
     * @brief Konstruktor klasy chart
     *
     *  Inicjalizuje widget wykresu danych z sensorów, wraz z trzema danymi pomiarowymi dla osi X,Y i Z
     *
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
chart::chart(QWidget *parent) : QWidget(parent) {
    plot = new QCustomPlot(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plot);

    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::red));

    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::blue));

    plot->addGraph();
    plot->graph(2)->setPen(QPen(Qt::green));

    plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(-2000, 2000);

    startTime = QDateTime::currentDateTime();
}

    /**
     * @brief Slot dodający nowe dane do wykresu
     *
     *  Inicjalizuje widget wykresu danych z sensorów, wraz z trzema danymi pomiarowymi dla osi X,Y i Z,
     *  reaguje na sygnał z danymi z klasy connection.
     *
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
void chart::onNewData(bool sensor, QStringList data){
    double key = startTime.msecsTo(QDateTime::currentDateTime()) / 1000.0;

    if(sensor){
        plot->graph(0)->addData(key, data[0].toDouble());
        plot->graph(1)->addData(key, data[1].toDouble());
        plot->graph(2)->addData(key, data[2].toDouble());
        plot->xAxis->setRange(key - 10, key);
        plot->replot();
    }
}
