#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QWidget>
#include <QMainWindow>

#include "connection.h"

/**
* \file
* \brief Definicja metody klasy menu
*
* Zawiera definicję metod klasy menu.
*/

namespace Ui {
class menu;
}

class MainWindow;

/**
 * @brief Klasa menu reprezentuje menu aplikacji Pong.
 *
 * Zawiera interfejs graficzny oparty na QDialog, który umożliwia dostęp do 4 przycisków:
 * wznowienia gry, rozpoczęcia nowej gry, wyjścia z gry oraz uruchomienia benchmarku
 */
class menu : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy menu.
     */
    explicit menu(MainWindow *mainWindow = nullptr,connection* connect = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~menu();

    connection* connectMenu;

private slots:
    /**
     * @brief Metoda obsługująca kliknięcie przycisku wznowienia gry.
     *
     * Powoduje wznowienie gry oraz zamknięcie okienka menu
     */
    void on_buttonGoBack_clicked();

    /**
     * @brief Metoda obsługująca kliknięcie przycisku wyjścia z gry.
     */
    void on_buttonExit_clicked();

    /**
     * @brief Metoda obsługująca kliknięcie przycisku nowej gry.
     */
    void on_buttonNewGame_clicked();

    /**
     * @brief Metoda obsługująca kliknięcie przycisku testowania połączenia.
     */
    void on_buttonTest_clicked();

signals:
    /**
     * @brief Sygnał wznawiający działanie gry
     *
     * Zostaje wysyłany w momencie kliknięcia przycisku wznowienia gry
     */
    void unPause();

    /**
     * @brief Sygnał restartujący działanie gry
     *
     * Zostaje wysyłany w momencie kliknięcia przycisku nowej gry
     */
    void restart();

private:
    /**
     * @brief Wskaźnik do obiektu interfejsu użytkownika.
     */
    Ui::menu *ui;

    /**
     * @brief Wskaźnik do rodzica klasy menu.
     */
    MainWindow *mainWindowPtr;
};

#endif // MENU_H
