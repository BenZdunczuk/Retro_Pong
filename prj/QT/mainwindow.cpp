#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include "ponging.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

/**
* \file
* \brief Definicja metody klasy MainWindow
*
* Zawiera definicję metod klasy MainWindow.
*/

    /**
     * @brief Konstruktor klasy MainWindow.
     *
     * Inicjalizuje okno graficzne oraz widget z grą Pong
     *
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isPaused(false)
{
    ui->setupUi(this);

    pongGame = new PongWidget(ui->gameWidget);
    QVBoxLayout *layout = new QVBoxLayout(ui->gameWidget);
    layout->addWidget(pongGame);

    pongGame->mainWindow = this;
}

    /**
     * @brief Destruktor klasy MainWindow.
     */
MainWindow::~MainWindow()
{
    delete ui;
}

    /**
     * @brief Metoda zamykająca główne okno aplikacji.
     */
void MainWindow::closeMainWindow() {
    this->close();
}

    /**
     * @brief Metoda obsługująca kliknięcie przycisku pauzy.
     *
     * Powoduje zatrzymanie gry oraz otworzenie okienka menu
     */
void MainWindow::on_buttonPause_clicked()
{
    togglePause();
    menu pMenu(this);
    pMenu.exec();

}

//     /**
//      * @brief Obsługuje przełączenie stanu przycisku pauzy (toggle).
//      * @param checked True, jeśli przycisk został wciśnięty; False w przeciwnym razie.
//      */
// void MainWindow::on_buttonPause_toggled(bool checked)
// {
//     isPaused = !isPaused;
//     pongGame->setPause(isPaused);
//     ui->buttonPause->setText(isPaused ? "Wznów" : "Pauza");
// }

    /**
     * @brief Przełącza stan gry (pomiędzy stanami: gra włączona i zatrzymana).
     */
void MainWindow::togglePause()
{
    isPaused = !isPaused;
    pongGame->setPause(isPaused);
    ui->buttonPause->setText(isPaused ? "Wznów" : "Pauza");
}

void MainWindow::resumedGame(){
    emit resumed();
}

