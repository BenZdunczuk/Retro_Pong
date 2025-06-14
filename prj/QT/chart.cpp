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
     * @param[in] parent Opcjonalny wskaźnik do rodzica.
     */
chart::chart(QWidget *parent) : QWidget(parent) {
    plot = new QCustomPlot(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plot);

    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::red));      //oś X

    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::blue));     //oś Y

    plot->addGraph();
    plot->graph(2)->setPen(QPen(Qt::green));    //oś Z

    plot->xAxis->setRange(0, 20);
    plot->yAxis->setRange(-5000, 5000);

    startTime = QDateTime::currentDateTime();
}

    /**
     * @brief Slot dodający nowe dane do wykresu
     *
     *  Inicjalizuje widget wykresu danych z sensorów, wraz z trzema danymi pomiarowymi dla osi X,Y i Z,
     *  reaguje na sygnał z danymi z klasy connection.
     *
     * @param[in] parent Opcjonalny wskaźnik do rodzica.
     */
void chart::onNewData(QStringList data){
    double key = startTime.msecsTo(QDateTime::currentDateTime()) / 1000.0;

    plot->graph(0)->addData(key, data[0].toDouble());
    plot->graph(1)->addData(key, data[1].toDouble());
    plot->graph(2)->addData(key, data[2].toDouble());
    plot->xAxis->setRange(key - 10, key);
    plot->replot();
}
