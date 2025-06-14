#include "mainwindow.h"
#include "menu.h"
#include "ui_menu.h"

#include <QIcon>

/**
* \file
* \brief Definicja metody klasy menu
*
* Zawiera definicję metod klasy menu.
*/

    /**
     * @brief Konstruktor klasy menu.
     * @param[in] parent Opcjonalny wskaźnik do rodzica.
     * @param[in] connect Wskaźnik do obiektu połączenia
     */
menu::menu(MainWindow *parent, connection* connect)
    : QDialog(parent), ui(new Ui::menu), mainWindowPtr(parent), connectMenu(connect), pTest(nullptr)
{
    ui->setupUi(this);

    if(mainWindowPtr->getTestOpen())
    ui->buttonTest->setEnabled(false);

    ui->buttonUS->setEnabled(true);
    ui->buttonPL->setEnabled(false);
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
    ui->buttonTest->setEnabled(false);
    mainWindowPtr->openTest();
}

    /**
     * @brief Slot odblokowujący możliwość naciśnięcia przycisku otwierającego okno testowe
     *
     * Slot odbiera sygnał wysyłany przez okno testu informujący o jego zamknięciu
     * i odblokowuje możliwość ponownego otworzenia okna testu przyciskiem
     */
void menu::unlockTestButton(){
    ui->buttonTest->setEnabled(true);
}

    /**
     * @brief Metoda obsługująca tłumaczenie ui okna klasy
     *
     * Uruchomiana podczas zmiany języka w menu aplikacji
     */
void menu::reTranslate(){
    ui->retranslateUi(this);
}


    /**
     * @brief Metoda obsługująca kliknięcie przycisku zmiany języka na angielski
     *
     * Powoduje zmianę języka aplikacji z polskiego na angielski
     * oraz zablokowanie tego przycisku i odblokowanie przycisku zmieniającego język na polski
     */
void menu::on_buttonUS_clicked(){
    mainWindowPtr->switchLanguage("en_US");
    ui->buttonUS->setEnabled(false);
    ui->buttonPL->setEnabled(true);
}

    /**
     * @brief Metoda obsługująca kliknięcie przycisku zmiany języka na polski
     *
     * Powoduje zmianę języka aplikacji z angielskiego na polski
     * oraz zablokowanie tego przycisku i odblokowanie przycisku zmieniającego język na angielski
     */
void menu::on_buttonPL_clicked(){
    mainWindowPtr->switchLanguage("pl_PL");
    ui->buttonUS->setEnabled(true);
    ui->buttonPL->setEnabled(false);
}
