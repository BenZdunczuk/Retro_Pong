#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QWidget>
#include <QMainWindow>

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
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
    explicit menu(MainWindow *mainWindow = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~menu();

private slots:
    /**
     * @brief Metoda obsługująca kliknięcie przycisku wznowienia gry.
     *
     * Powoduje wznowienie gry oraz zamknięcie okienka menu
     */
    void on_buttonGoBack_clicked();

    /**
     * @brief Metoda obsługująca kliknięcie przycisku wyjścia z gry.
     *
     * Powoduje zatrzymanie działania aplikacji
     */
    void on_buttonExit_clicked();

    /**
     * @brief Metoda obsługująca kliknięcie przycisku nowej gry.
     *
     * Powoduje zresetowanie gry oraz zamknięcie okienka menu
     */
    void on_buttonNewGame_clicked();

    /**
     * @brief Metoda obsługująca kliknięcie przycisku testowania połączenia.
     *
     * Powoduje otworzenie okienka testowania połączenia
     */
    void on_buttonTest_clicked();

signals:
    void unPause();

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
