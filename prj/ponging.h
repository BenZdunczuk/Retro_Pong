#ifndef PONGING_H
#define PONGING_H

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

    /**
     * @brief Metoda typu getter umożliwiająca dostęp do atrybutu score
     */
    int getScore();

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
     * @brief Flaga informująca o stanie gry (zatrzymana/trwająca)
     */
    bool isPaused;

    /**
     * @brief Atrybut przechowujący aktualny wynik w grze
     */
    int score;

    /**
     * @brief Współrzędne piłęczki
     */
    int ballDX, ballDY;

    /**
     * @brief Kierunek poruszania i obracania się piłeczki
     */
    bool moveUp, moveDown, rotateRight, rotateLeft;

    int rotationAngle;
    int posX,posY;

    /**
     * @brief Zegar gry wykorzystywany do odświeżania animacji
     */
    QTimer *timer;

    /**
     * @brief Metoda resetująca pozycję piłeczki
     */
    void resetBall();
};

#endif // PONGING_H
