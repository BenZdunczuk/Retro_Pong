#include "Ponging.h"
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
    : QWidget(parent),mainWindow(nullptr), ballDX(baseSpeed), ballDY(baseSpeed),
    rotationAnglePaddle(0), isPaused(false), scoreAI(0), scorePlayer(0), posX(0), posY(0),
    rotationAngleBall(45), speed(baseSpeed)
{
    setFocusPolicy(Qt::StrongFocus);

    QObject::connect(connect,&connection::dataProcessed,this,&PongWidget::calculateMovement);

    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &PongWidget::gameLoop);
    int t = 16;         // okres odświeżania w ms - odpowiada 60hz
    timer->start(t);
}

    /**
     * @brief Metoda inicjalizująca parametry w grze uruchamiana po otworzeniu widgetu
     *
     * Inicjalizacja musi nastąpić po utworzeniu obiektu aby rozmiar widgetu został poprawnie określony
     *
     * @param[in] event Wskaźnik do zdarzenia pokazania widgetu
     */
void PongWidget::showEvent(QShowEvent* event){

    // inicjalizacja wymiarów i lokalizacji obiektów do rysowania
    aiPaddle = QRect(20, height()/2 - 40, 10, 60);
    playerPaddle = QRect(-5,height()/2 - 40, 10, 60);
    posY = height()/2 - 20;
    posX = width() - 40;
    // std::cout << "X:" << width() << " Y:" << height() << std::endl;
    ball = QRect(width()/2 - 10, width()/2 - 10, 20, 20);
}

    /**
     * @brief Metoda dostosowująca parametry w grze po dynamicznym skalowaniu okna przez użytkownika
     *
     * Resetowana jest pozycja piłeczki aby nie dopuścić do niesportowych zachowań zmiany wielkości
     * okienka w trakcie gry
     *
     * @param[in] event Wskaźnik do zdarzenia zmiany wielkości widgetu
     */
void PongWidget::resizeEvent(QResizeEvent* event){
    aiPaddle = QRect(20, height()/2 - 40, 10, 60);
    playerPaddle = QRect(-5,height()/2 - 40, 10, 60);
    posY = height()/2 - 20;
    posX = width() - 40;

    resetBall();
}


    /**
     * @brief Metoda inicjalizująca rysowanie gry
     *
     * Rysuje boisko (obszar do gry), paletki i piłeczkę
     *
     * @param[in] event Opcjonalny wskaźnik do rysowania.
     */
void PongWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::black);
    painter.setBrush(Qt::white);

    painter.save();
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);

    painter.drawLine(0,height(),width(),height());  // Rysowanie linii bocznych z góry i dołu
    painter.drawLine(0,0,width(),0);

    pen.setStyle(Qt::DashLine);  // Rysowanie linii przerywanej
    painter.setPen(pen);
    painter.drawLine(width()/2, height() - 10, width()/2, 10);
    painter.restore();

    //obrót paletki poprzez przeniesienie we współrzędne 0,0, wykonanie obrotu i zwrócenie na poprzednie miejsce
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
    painter.drawText(width()/4 - 10, 0.1*height(), QString("%1").arg(scoreAI));
    painter.drawText(3*width()/4 - 10, 0.1*height(), QString("%1").arg(scorePlayer));
}

    /**
     * @brief Metoda obsługująca grę, wykonywana w pętli
     *
     * Obsługuje ruch piłki i paletki przeciwnika, obsługuje fizykę gry (odbicia)
     * oraz sprawdza warunki zdobycia punktów (piłka wypada poza boisko)
     *
     */
void PongWidget::gameLoop(){
    QEventLoop pausedLoop;
    connect(mainWindow,&MainWindow::resumed, &pausedLoop, &QEventLoop::quit);
    connect(mainWindow,&MainWindow::restarted, &pausedLoop, &QEventLoop::quit);
    if(isPaused) pausedLoop.exec();

    connect(mainWindow,&MainWindow::restarted,this,&PongWidget::resetGame);

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
     * Interpretuje dane z czujników,reaguje na sygnał wysyłany z okna głównego z klasy connection
     *
     *@param[in] data przetworzone dane odczytane z czujników w formacie typu string
     *@param[out] posY zmienna określająca położenie paletki w pikselach
     *@param[out] rotationAngleBall zmienna określająca obrót paletki w stopniach
     */
void PongWidget::calculateMovement(QStringList data){
    //próg dla wartości sensora, po których jest odczytywany ruch liniowy i obrotowy paletki
    int thresholdLinear = 2000;
    int thresholdAngular = 4000;

    //minimalne i maksymalne wartości możliwego ruchu
    int minStepLinear = 5;
    int maxStepLinear = 20;
    int minStepAngular = 1;
    int maxStepAngular = 5;

    //zmiana pozycji(piksele) i kąta(stopnie) paletki
    int da = 0;
    int dy = 0;

    //interpretacja danych z osi Y -- ruch paletki
    if (data[1].toInt() < -thresholdLinear) {
        dy = (((-data[1].toInt() - thresholdLinear) / 1000) + minStepLinear);
        if (dy > maxStepLinear) dy = maxStepLinear;
    } else if (data[1].toInt() > thresholdLinear) {
        dy = -(((data[1].toInt() - thresholdLinear) / 1000) + minStepLinear);
        if (dy < -maxStepLinear) dy = -maxStepLinear;
    }
    if(posY > 0 && posY < height()) posY += dy;
    else if(posY <= 0) posY = 1;
    else if(posY >= height()) posY = height()-1;

    //interpretacja danych z osi X -- obrót paletki
    if (data[0].toInt() < -thresholdAngular) {
        da = (((-data[0].toInt() - thresholdAngular) / 1000) + minStepAngular);
        if (da > maxStepAngular) da = maxStepAngular;
    } else if (data[0].toInt() > thresholdAngular) {
        da = -(((data[0].toInt() - thresholdAngular) / 1000) + minStepAngular);
        if (da < -maxStepAngular) da = -maxStepAngular;
    }
    if(posY > 0 && posY < height()) rotationAnglePaddle += da;
    rotationAnglePaddle %= 360;
}
