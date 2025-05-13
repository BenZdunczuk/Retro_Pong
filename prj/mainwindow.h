#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include "ponging.h"
#include "menu.h"

/**
* \file
* \brief Definicja metody klasy MainWindow
*
* Zawiera definicję metod klasy MainWindow.
*/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Klasa MainWindow reprezentuje główne okno aplikacji Pong.
 *
 * Zawiera interfejs graficzny oparty na QMainWindow, który integruje komponent do gry Pong
 * oraz przycisk sterujący pauzowaniem gry.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy MainWindow.
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~MainWindow();

    /**
     * @brief Metoda zamykająca główne okno aplikacji.
     */
    void closeMainWindow();

    /**
     * @brief Przełącza stan gry (pomiędzy stanami: gra włączona i zatrzymana).
     */
    void togglePause();

private slots:
    /**
     * @brief Metoda obsługująca kliknięcie przycisku pauzy.
     */
    void on_buttonPause_clicked();

    /**
     * @brief Obsługuje przełączenie stanu przycisku pauzy (toggle).
     * @param checked True, jeśli przycisk został wciśnięty; False w przeciwnym razie.
     */
    //void on_buttonPause_toggled(bool checked);

private:
    /**
     * @brief Wskaźnik do obiektu interfejsu użytkownika.
     */
    Ui::MainWindow *ui;

    /**
     * @brief Wskaźnik do widżetu gry Pong.
     */
    PongWidget *pongGame;

    /**
     * @brief Flaga informująca, czy gra jest obecnie zatrzymana.
     */
    bool isPaused;

public slots:
    void resumedGame();


signals:
    void resumed();
};

#endif // MAINWINDOW_H
