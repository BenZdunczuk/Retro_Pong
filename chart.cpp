#include "chart.h"
#include <QPainter>
#include <QtMath>
#include <QTimer>

/**
 * @brief
 *
 * @param
 * @return
 */
chart::chart(QWidget *parent,double setPhase)
    : QWidget{parent}
{
    phase = setPhase;
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &chart::onTimeout);
    timer->start(100);
}

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

void chart::onTimeout()
{
    phase += 0.05;
    update();
}
