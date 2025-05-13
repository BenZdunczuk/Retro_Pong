#include "Ponging.h"
#include "menu.h"
#include "mainwindow.h"
#include <QPainter>
#include <cmath>
#include <QEventLoop>

/**
* \file
* \brief Definicja metody klasy PongWidget
*
* Zawiera definicję metod klasy PongWidget.
*/

#define baseSpeed 4

/**
     * @brief Konstruktor klasy menu.
     *
     * Określa wymiary widgetu gry, inicjalizuje obiekty paletek oraz piłeczki,
     * inicjalizuje QTimer używany to aktualizowania rysowania gry
     *
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
PongWidget::PongWidget(QWidget *parent)
    : QWidget(parent), mainWindow(nullptr), ballDX(baseSpeed), ballDY(baseSpeed), moveUp(false), moveDown(false), rotateRight(false),
    rotateLeft(false),rotationAnglePaddle(0), isPaused(false), score(0), posX(0), posY(0), rotationAngleBall(45), speed(baseSpeed)
{
    setFocusPolicy(Qt::StrongFocus);

    // width oraz height - wymiary gry
    int w = 800;
    int h = 600;

    resize(w, h);

    // inicjalizacja wymiarów i lokalizacji obiektów do rysowania
    aiPaddle = QRect(20, h/2 - 40, 10, 60);
    playerPaddle = QRect(-5, -40, 10, 60);
    posY = 280;
    posX = 760;
    ball = QRect(w/2 - 10, h/2 - 10, 20, 20);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PongWidget::gameLoop);
    int t = 16;         // okres odświeżania w ms - odpowiada 60hz
    timer->start(t);
}

    /**
     * @brief Metoda inicjalizująca rysowanie gry
     *
     * Rysuje boisko (obszar do gry), paletki i piłeczkę
     *
     * @param event Opcjonalny wskaźnik do rysowania.
     */
void PongWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::black);

    painter.setBrush(Qt::white);

    painter.save();
    playerPaddle.moveTo(-5,-30);
    painter.translate(posX,posY);
    painter.rotate(rotationAnglePaddle);
    painter.translate(playerPaddle.center());
    painter.drawRect(playerPaddle);
    playerPaddle.moveTo(posX-5,posY-30);
    painter.restore();

    painter.drawRect(aiPaddle);
    painter.drawEllipse(ball);

}

    /**
     * @brief Metoda reagująca na kliknięcie przycisku strzałek na klawiaturze
     * @param event Opcjonalny wskaźnik do rysowania.
     */
void PongWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) moveUp = true;
    if (event->key() == Qt::Key_Down) moveDown = true;
    if (event->key() == Qt::Key_Right) rotateRight = true;
    if (event->key() == Qt::Key_Left) rotateLeft = true;
}

    /**
     * @brief Metoda reagująca na zwolnienie przycisku strzałek na klawiaturze
     * @param event Opcjonalny wskaźnik do rysowania.
     */
void PongWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) moveUp = false;
    if (event->key() == Qt::Key_Down) moveDown = false;
    if (event->key() == Qt::Key_Right) rotateRight = false;
    if (event->key() == Qt::Key_Left) rotateLeft = false;
}

    /**
     * @brief Metoda obsługująca grę, wykonywana w pętli
     *
     * Obsługuje poruszanie paletką przez gracza, poruszanie paletką przez przeciwnika
     * oraz obsługuje fizykę gry
     *
     */
void PongWidget::gameLoop()
{
    QEventLoop loop;
    connect(mainWindow,&MainWindow::resumed, &loop, &QEventLoop::quit);
    if(isPaused){

        loop.exec();

    }

    /*      gracz       */
    if (moveUp && posY > 0)
        //playerPaddle.moveTop(playerPaddle.top() - 6);
        posY -= 6;
    if (moveDown && posY < height())
        //playerPaddle.moveTop(playerPaddle.top() + 6);
        posY += 6;
    if(rotateLeft)
        --rotationAnglePaddle;
    if(rotateRight)
        ++rotationAnglePaddle;

    /*      ai      */
    if (aiPaddle.center().y() < ball.center().y() && aiPaddle.bottom() < height())
        aiPaddle.moveTop(aiPaddle.top() + 4);
    else if (aiPaddle.center().y() > ball.center().y() && aiPaddle.top() > 0)
        aiPaddle.moveTop(aiPaddle.top() - 4);

    /*      ruch piłki      */
    ball.translate(ballDX, ballDY);

    /*      odbicia     */
    if (ball.top() <= 0 || ball.bottom() >= height())
        rotationAngleBall = rotation(reflaction(rotationAngleBall,180));

    if (ball.intersects(playerPaddle) && ballDX > 0)
        rotationAngleBall = rotation(reflaction(rotationAngleBall,rotationAnglePaddle + 90));
        //ballDX = -ballDX;
    if (ball.intersects(aiPaddle) && ballDX < 0)
        rotationAngleBall = rotation(reflaction(rotationAngleBall,90));
        //ballDX = -ballDX;

    /*      piłeczka wypada poza boisko     */
    if (ball.left() < 0 || ball.right() > width())
        //score++;
        resetBall();

    update();
}

    /**
     * @brief Metoda resetująca pozycję piłeczki
     *
     * Wykonywana w momencie stracenia punktu przez gracza
     * lub w momencie resetu całej gry
     */
void PongWidget::resetBall()
{
    speed = baseSpeed;
    ball.moveTo(width()/2 - 10, height()/2 - 10);
    rotationAngleBall = 180-rotationAngleBall;      //zmiana kierunku piłeczki po wypadnięciu z boiska
    rotation(rotationAngleBall);
}

    /**
     * @brief Metoda typu setter umożliwiająca dostęp do modyfikacji atrybutu paused
     * @param paused Stan gry (zatrzymana/trwająca)
     */
void PongWidget::setPause(bool pause)
{
    isPaused = pause;
}

    /**
     * @brief Metoda typu getter umożliwiająca dostęp do atrybutu score
     */
int PongWidget::getScore()
{
    return score;
}

    /**
     * @brief Metoda obliczająca długości wektorów składowych piłeczek
     * @param[in] angle Kąt obrotu piłeczki względem osi OX
     * @param[out] angle Kąt obrotu piłeczki modulo 360, jakby doszło do zatoczenia pełnego koła
     */
int PongWidget::rotation(int angle){
    angle %= 360;
    speed *= 1.1;
    ballDX = speed * 1.41 * cos(3.14*angle/180);
    ballDY = speed * 1.41 * sin(3.14*angle/180);
    return angle;
}

    /**
     * @brief Metoda typu getter umożliwiająca dostęp do atrybutu score
     * @param[in] angle Kąt obrotu obiektu względem osi OX
     * @param[out] angle Kąt obrotu modulo 360, jakby doszło do zatoczenia pełnego koła
     */
int PongWidget::reflaction(int angleA, int angleB){
    angleA = 2*angleB - angleA;
    return angleA;
}
