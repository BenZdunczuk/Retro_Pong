#include "Ponging.h"
#include "menu.h"
#include "mainwindow.h"
#include <QPainter>
#include <cmath>
#include <QEventLoop>
#include <random>
// #include <iostream>

/**
* \file
* \brief Definicja metody klasy PongWidget
*
* Zawiera definicję metod klasy PongWidget.
*/

#define baseSpeed 4

    /**
     * @brief Konstruktor klasy PongWidget.
     *
     * Określa wymiary widgetu gry, inicjalizuje obiekty paletek oraz piłeczki,
     * inicjalizuje QTimer używany to aktualizowania rysowania gry
     *
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
PongWidget::PongWidget(QWidget *parent, connection *connect)
    : QWidget(parent),mainWindow(nullptr), connectPong(connect), ballDX(baseSpeed), ballDY(baseSpeed), moveUp(false), moveDown(false), rotateRight(false),
    rotateLeft(false),rotationAnglePaddle(0), isPaused(false), scoreAI(0), scorePlayer(0), posX(0), posY(0), rotationAngleBall(45), speed(baseSpeed)
{
    setFocusPolicy(Qt::StrongFocus);

    QObject::connect(connectPong,&connection::dataProcessed,this,&PongWidget::calculateMovement);


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
    QObject::connect(timer, &QTimer::timeout, this, &PongWidget::gameLoop);
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

    painter.setPen(Qt::white);
    painter.setFont(QFont("Courier", 16));
    painter.drawText(10, 30, QString("Wynik: %1").arg(scoreAI));
    painter.drawText(660, 30, QString("Wynik: %1").arg(scorePlayer));
}

    /**
     * @brief Metoda reagująca na kliknięcie przycisku strzałek na klawiaturze
     * @param event Opcjonalny wskaźnik do rysowania.
     */
void PongWidget::keyPressEvent(QKeyEvent *event){
    // if (event->key() == Qt::Key_Up) moveUp = true;
    // if (event->key() == Qt::Key_Down) moveDown = true;
    // if (event->key() == Qt::Key_Right) rotateRight = true;
    // if (event->key() == Qt::Key_Left) rotateLeft = true;
}

    /**
     * @brief Metoda reagująca na zwolnienie przycisku strzałek na klawiaturze
     * @param event Opcjonalny wskaźnik do rysowania.
     */
void PongWidget::keyReleaseEvent(QKeyEvent *event){
    // if (event->key() == Qt::Key_Up) moveUp = false;
    // if (event->key() == Qt::Key_Down) moveDown = false;
    // if (event->key() == Qt::Key_Right) rotateRight = false;
    // if (event->key() == Qt::Key_Left) rotateLeft = false;
}

    /**
     * @brief Metoda obsługująca grę, wykonywana w pętli
     *
     * Obsługuje poruszanie paletką przez gracza, poruszanie paletką przez przeciwnika
     * oraz obsługuje fizykę gry
     *
     */
void PongWidget::gameLoop(){
    QEventLoop pausedLoop;
    connect(mainWindow,&MainWindow::resumed, &pausedLoop, &QEventLoop::quit);
    connect(mainWindow,&MainWindow::restarted, &pausedLoop, &QEventLoop::quit);
    if(isPaused){
        pausedLoop.exec();
    }

    connect(mainWindow,&MainWindow::restarted,this,&PongWidget::resetGame);

    /*      gracz       */
    if (moveUp && posY > 0)
        posY -= 6;
    if (moveDown && posY < height())
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
    if (ball.intersects(aiPaddle) && ballDX < 0)
        rotationAngleBall = rotation(reflaction(rotationAngleBall,90));

    /*      piłeczka wypada poza boisko     */
    if (ball.left() < 0){   //wypada ze strony AI
        ++scorePlayer;
        resetBall();
    }

    if (ball.right() > width()){   //wypada ze strony gracza
        ++scoreAI;
        resetBall();
    }

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
    rotationAngleBall = 45*rotationAngleBall/abs(rotationAngleBall);    //zmiana kierunku piłeczki po wypadnięciu z boiska
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);         //randomizacja kierunku piłeczki
    rotationAngleBall += 90*dist(gen);
    rotation(rotationAngleBall);
}

    /**
     * @brief Metoda typu setter umożliwiająca dostęp do modyfikacji atrybutu paused
     * @param[in] paused Stan gry (zatrzymana/trwająca)
     */
void PongWidget::setPause(bool pause)
{
    isPaused = pause;
}

    /**
     * @brief Metoda obliczająca długości wektorów składowych piłeczek
     * @param[in] angle Kąt obrotu piłeczki względem osi OX
     * @param[out] angle Kąt obrotu piłeczki modulo 360, jakby doszło do zatoczenia pełnego koła
     */
int PongWidget::rotation(int angle){
    speed *= 1.05;      //przyśpieszenie gry
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

    /**
     * @brief Metoda resetująca aktualną grę
     */
void PongWidget::resetGame(){
    scoreAI = 0;
    scorePlayer = 0;
    resetBall();
}

    /**
     * @brief Metoda interpretująca odczyty sensorów i przekładająca je na sterowanie w grze
     *
     * Reaguje na sygnał z danymi z czujników, wysyłany z okna głównego z klasy connection
     *
     *@param[in] sensor zmienna określająca typ czujnika (0 - żyroskop, 1 - akcelerometr)
     *@param[in] data przetworzone dane odczytane z czujników w formacie typu string
     *@param[out] moveDown zmienna boolowska określająca czy ruch paletki w dół ma następować czy nie
     *@param[out] moveUp zmienna boolowska określająca czy ruch paletki w górę ma następować czy nie
     */
void PongWidget::calculateMovement(bool sensor, QStringList data){
    int threshold = 1000;       //próg dla wartości sensora, po których jest odczytywany ruch

    if(sensor){
        if(data[0].toInt() > threshold){
            moveUp = true;
        } else if(data[0].toInt() < -threshold){
            moveDown = true;
        } else {
            moveUp = false;
            moveDown = false;
        }
    }
}
