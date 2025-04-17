#include "chart.h"
#include <QPainter>
#include <QtMath>

chart::chart(QWidget *parent)
    : QWidget{parent}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void chart::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    int centerX = w / 2;
    int centerY = h / 2;

    // Rysuj osie
    painter.setPen(Qt::black);
    painter.drawLine(0, centerY, w, centerY); // X
    painter.drawLine(centerX, 0, centerX, h); // Y

    // Skala X: jeden cykl sinusa na szerokości okna
    double xStep = (2 * M_PI) / w;

    // Skala Y: sinus od -1 do 1 przeskalowany na wysokość
    double yScale = h / 2.0;

    // Rysuj wykres
    painter.setPen(QPen(Qt::blue, 2));
    QPoint prev;

    for (int px = 0; px < w; ++px) {
        double x = xStep * (px - w / 2);      // przesunięcie względem środka
        double y = qSin(x);                   // y = sin(x)
        int py = centerY - int(y * yScale);   // odwrotność osi Y

        if (px > 0)
            painter.drawLine(prev, QPoint(px, py));

        prev = QPoint(px, py);
    }
}
