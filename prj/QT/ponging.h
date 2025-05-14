#ifndef PONGING_H
#define PONGING_H

#include "menu.h"
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>

/**
* \file
* \brief Definicja metody klasy PongWidget
*
* Zawiera definicję metod klasy PongWidget.
*/

/**
 * @brief Klasa PongWidget reprezentuje widget wyświetlający grę Pong
 *
 * Zawiera interfejs graficzny oparty na QWidget, który wyświetla grę Pong
 */
class PongWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy menu.
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
    explicit PongWidget(QWidget *parent = nullptr);

    /**
     * @brief Metoda typu setter umożliwiająca dostęp do atrybutu paused
     * @param paused Stan gry (zatrzymana/trwająca)
     */
    void setPause(bool paused);

    MainWindow *mainWindow;

protected:
    /**
     * @brief Metoda inicjalizująca rysowanie wykresu
     * @param event Opcjonalny wskaźnik do rysowania.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Metoda reagująca na kliknięcie przycisku strzałki w górę i w dół
     * @param event Opcjonalny wskaźnik do rysowania.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Metoda reagująca na kliknięcie przycisku strzałki w górę i w dół
     * @param event Opcjonalny wskaźnik do rysowania.
     */
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    /**
     * @brief Metoda obsługująca grę, wykonywana w pętli
     */
    void gameLoop();

private:
    /**
     * @brief Obiekt symulujący paletkę gracza
     */
    QRect playerPaddle;

    /**
     * @brief Obiekt symulujący paletkę przeciwnika
     */
    QRect aiPaddle;

    /**
     * @brief Obiekt symulujący piłeczkę
     */
    QRect ball;

    /**
     * @brief Metoda obliczająca długości wektorów składowych piłeczek
     */
    int rotation(int angle);

    /**
     * @brief Metoda typu getter umożliwiająca dostęp do atrybutu score
     */
    int reflaction(int angleA, int angleB);

    /**
     * @brief Flaga informująca o stanie gry (zatrzymana/trwająca)
     */
    bool isPaused;

    /**
     * @brief Atrybut przechowujący aktualny wynik obu graczy w grze
     */
    int scoreAI,scorePlayer;

    /**
     * @brief Współrzędne piłęczki
     */
    int ballDX, ballDY;

    /**
     * @brief Kierunek poruszania i obracania się piłeczki
     */
    bool moveUp, moveDown, rotateRight, rotateLeft;

    /**
     * @brief Kąt obrotu oraz pozycja paletki
     */
    int rotationAnglePaddle,posX,posY;
    int rotationAngleBall;

    /**
     * @brief Prędkość poruszania się piłęczki
     */
    double speed;

    /**
     * @brief Zegar gry wykorzystywany do odświeżania animacji
     */
    QTimer *timer;

    /**
     * @brief Metoda resetująca pozycję piłeczki
     */
    void resetBall();

public slots:
    /**
     * @brief Metoda resetująca aktualną grę
     */
    void resetGame();
};

#endif // PONGING_H
