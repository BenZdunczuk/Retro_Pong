#include "chart.h"
#include <QPainter>
#include <QtMath>
#include <QTimer>

/**
* \file
* \brief Definicja metody klasy chart
*
* Zawiera definicję metod klasy chart.
*/

    /**
     * @brief Konstruktor klasy chart.
     *
     * Inicjalizuje QTimer wykorzystywany do przesuwania wykresu,
     * ustawia wartość początkowego przesunięcia fazowego
     *
     * @param parent Opcjonalny wskaźnik do rodzica.
     * @param setPhase Przesunięcie fazowe sinusa (tylko w wersji do testowania wyświetlania wykresu)
     */
chart::chart(QWidget *parent,double setPhase)
    : QWidget{parent}
{
    phase = setPhase;
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &chart::onTimeout);
    int t = 100;        // okres próbkowania w ms
    timer->start(t);
}

    /**
     * @brief Metoda inicjalizująca rysowanie wykresu
     *
     * Określa wymiary wykresu, rysuje osie oraz sam wykres,
     * przesuwa wykres w czasie
     *
     * @param event Opcjonalny wskaźnik do rysowania.
     */
void chart::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();

    int centerX = width / 2;
    int centerY = height / 2;

    double xScale = 50.0;
    double yScale = 50.0;

    painter.setPen(QPen(Qt::gray, 1));
    painter.drawLine(0, centerY, width, centerY);
    painter.drawLine(centerX, 0, centerX, height);

    painter.setPen(QPen(Qt::blue, 2));

    QPointF previousPoint;

    for (int i = 0; i < width; ++i) {
        double x = (i - centerX) / xScale;
        double y = qSin(x + phase);
        double yPixel = centerY - y * yScale;

        QPointF currentPoint(i, yPixel);

        if (i > 0) {
            painter.drawLine(previousPoint, currentPoint);
        }

        previousPoint = currentPoint;
    }
}

    /**
     * @brief Slot odpoweidzialny za przesuwanie wykresu w czasie
     *
     * Zwiększa wartość przesunięcia fazowego oraz aktualizuje wykres,
     * funkcja wywoływana przez QTimer zawarty w konstruktorze
     */
void chart::onTimeout()
{
    phase += 0.05;
    update();
}
