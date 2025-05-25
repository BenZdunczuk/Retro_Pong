#include "mainwindow.h"
#include "test.h"
#include "menu.h"
#include "ui_menu.h"

/**
* \file
* \brief Definicja metody klasy menu
*
* Zawiera definicję metod klasy menu.
*/

    /**
     * @brief Konstruktor klasy menu.
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
menu::menu(MainWindow *parent, connection* connect)
    : QDialog(parent), ui(new Ui::menu), mainWindowPtr(parent), connectMenu(connect)
{
    ui->setupUi(this);
}

    /**
     * @brief Destruktor klasy MainWindow.
     */
menu::~menu()
{
    delete ui;
}

    /**
     * @brief Metoda obsługująca kliknięcie przycisku wznowienia gry.
     *
     * Powoduje wznowienie gry oraz zamknięcie okienka menu
     */
void menu::on_buttonGoBack_clicked()
{
    connect(this,&menu::unPause,mainWindowPtr,&MainWindow::resumedGame);
    mainWindowPtr->togglePause();
    menu::close();
    emit unPause();
}

    /**
     * @brief Metoda obsługująca kliknięcie przycisku wyjścia z gry.
     *
     * Powoduje zatrzymanie działania aplikacji oraz zamyka wszystkie okienka
     */
void menu::on_buttonExit_clicked()
{
    menu::close();
    mainWindowPtr->closeMainWindow();
}

    /**
     * @brief Metoda obsługująca kliknięcie przycisku nowej gry.
     *
     * Powoduje zresetowanie gry oraz zamknięcie okienka menu
     */
void menu::on_buttonNewGame_clicked()
{
    connect(this,&menu::restart,mainWindowPtr,&MainWindow::restartedGame);
    mainWindowPtr->togglePause();
    menu::close();
    emit restart();
}

    /**
     * @brief Metoda obsługująca kliknięcie przycisku testowania połączenia.
     *
     * Powoduje otworzenie okienka testowania połączenia
     */
void menu::on_buttonTest_clicked()
{
    test pTest(this,connectMenu);
    pTest.exec();
}

