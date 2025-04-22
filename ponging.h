#ifndef PONGING_H
#define PONGING_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>

class PongWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PongWidget(QWidget *parent = nullptr);
    void setPause(bool paused);
    int getScore();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void gameLoop();

private:
    QRect playerPaddle;
    QRect aiPaddle;
    QRect ball;

    bool isPaused;

    int score;

    int ballDX, ballDY;
    bool moveUp, moveDown;

    QTimer *timer;

    void resetBall();
};

#endif // PONGING_H
