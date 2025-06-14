#ifndef PONGING_H
#define PONGING_H

#pragma once

#include "connection.h"
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>

/**
* \file
* \brief Definicja metody klasy PongWidget
*
* Zawiera definicję metod klasy PongWidget.
*/

class MainWindow;

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
     * @brief Konstruktor klasy PongWidget.
     */
    explicit PongWidget(QWidget *parent = nullptr,connection *connect = nullptr);

    /**
     * @brief Metoda typu setter umożliwiająca dostęp do atrybutu paused
     */
    void setPause(bool paused);

    /**
     * @brief Zmienna przechowująca wskaźnik do obiektu okna głównego
     */
    MainWindow *mainWindow;

protected:
    /**
     * @brief Metoda inicjalizująca rysowanie wykresu
     */
    void paintEvent(QPaintEvent *event) override;

private slots:
    /**
     * @brief Metoda obsługująca grę, wykonywana w pętli
     */
    void gameLoop();

    /**
     * @brief Metoda interpretująca odczyty sensorów i przekładająca je na sterowanie w grze
     */
    void calculateMovement(QStringList data);

private:

    /**
     * @brief Metoda inicjalizująca parametry w grze, uruchamiana po otworzeniu widgetu
     */
    void showEvent(QShowEvent* event) override;

    /**
     * @brief Metoda dostosowująca parametry w grze po dynamicznym skalowaniu okna przez użytkownika
     */
    void resizeEvent(QResizeEvent* event) override;

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
     * @brief Kąt obrotu oraz pozycja paletki
     */
    int rotationAnglePaddle,posX,posY;

    /**
     * @brief Kąt obrotu piłeczki
     */
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
