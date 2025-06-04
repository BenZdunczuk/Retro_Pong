#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <qdatetime.h>
#include "qcustomplot.h"

/**
* \file
* \brief Definicja klasy chart
*
* Zawiera definicję klasy chart.
*/

/**
 * @brief Klasa chart reprezentuje wykresy używane do wizualizacji danych
 *
 * Zawiera definicję widgetu rysującego wykres na podstawie danych odebranych z mikrokontrolera.
 */
class chart : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy chart
     */
    chart(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Slot dodający nowe dane do wykresu
     */
    void onNewData(QStringList data);

private:
    /**
     * @brief Zmienna przechowująca wskażnik do wykresu
     */
    QCustomPlot *plot;

    /**
     * @brief Zmienna przechowująca czas rozpoczęcia pokazywania danych
     */
    QDateTime startTime;
};

#endif // CHART_H
