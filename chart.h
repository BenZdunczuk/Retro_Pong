#ifndef CHART_H
#define CHART_H

#include <QWidget>

class chart : public QWidget
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = nullptr,double setPhase = 0.0);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onTimeout();

private:
    double phase;

signals:
};

#endif // CHART_H
