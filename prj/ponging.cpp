#include "Ponging.h"
#include <QPainter>

/**
* \file
* \brief Definicja metody klasy PongWidget
*
* Zawiera definicję metod klasy PongWidget.
*/

/**
     * @brief Konstruktor klasy menu.
     *
     * Określa wymiary widgetu gry, inicjalizuje obiekty paletek oraz piłeczki,
     * inicjalizuje QTimer używany to aktualizowania rysowania gry
     *
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
PongWidget::PongWidget(QWidget *parent)
    : QWidget(parent), ballDX(4), ballDY(4), moveUp(false), moveDown(false), isPaused(false), score(0)
{
    setFocusPolicy(Qt::StrongFocus);

    // width oraz height - wymiary gry
    int w = 800;
    int h = 600;

    resize(w, h);

    // inicjalizacja wymiarów i lokalizacji obiektów do rysowania
    aiPaddle = QRect(20, h/2 - 40, 10, 80);
    playerPaddle = QRect(w - 30, h/2 - 40, 10, 80);
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
    painter.drawRect(playerPaddle);
    painter.drawRect(aiPaddle);
    painter.drawEllipse(ball);

    // if (isPaused) {
    //     painter.setPen(Qt::yellow);
    //     painter.setFont(QFont("Arial", 24, QFont::Bold));
    //     painter.drawText(rect(), Qt::AlignCenter, "PAUZA");
    // }

    // painter.setPen(Qt::green);
    // painter.setFont(QFont("Courier", 16));
    // painter.drawText(10, 30, QString("Wynik: %1").arg(getScore()));
}

    /**
     * @brief Metoda reagująca na kliknięcie przycisku strzałki w górę i w dół
     * @param event Opcjonalny wskaźnik do rysowania.
     */
void PongWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) moveUp = true;
    if (event->key() == Qt::Key_Down) moveDown = true;
}

    /**
     * @brief Metoda reagująca na kliknięcie przycisku strzałki w górę i w dół
     * @param event Opcjonalny wskaźnik do rysowania.
     */
void PongWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) moveUp = false;
    if (event->key() == Qt::Key_Down) moveDown = false;
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
    //if (isPaused) return;

    /*      gracz       */
    if (moveUp && playerPaddle.top() > 0)
        playerPaddle.moveTop(playerPaddle.top() - 6);
    if (moveDown && playerPaddle.bottom() < height())
        playerPaddle.moveTop(playerPaddle.top() + 6);

    /*      ai      */
    if (aiPaddle.center().y() < ball.center().y() && aiPaddle.bottom() < height())
        aiPaddle.moveTop(aiPaddle.top() + 4);
    else if (aiPaddle.center().y() > ball.center().y() && aiPaddle.top() > 0)
        aiPaddle.moveTop(aiPaddle.top() - 4);

    /*      odbicia     */
    ball.translate(ballDX, ballDY);

    if (ball.top() <= 0 || ball.bottom() >= height())
        ballDY = -ballDY;

    if (ball.intersects(playerPaddle) && ballDX > 0)
        ballDX = -ballDX;
    if (ball.intersects(aiPaddle) && ballDX < 0)
        ballDX = -ballDX;

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
    ball.moveTo(width()/2 - 10, height()/2 - 10);
    ballDX = -ballDX;
    ballDY = 4;
}

    /**
     * @brief Metoda typu setter umożliwiająca dostęp do atrybutu paused
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
