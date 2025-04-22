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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isPaused(false)
{
    ui->setupUi(this);

    PongWidget *game = new PongWidget(ui->gameWidget);
    QVBoxLayout *layout = new QVBoxLayout(ui->gameWidget);
    layout->addWidget(game);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeMainWindow() {
    this->close();
}

void MainWindow::on_buttonPause_clicked()
{
    //menu *pMenu = new menu(this);
    menu pMenu(this);

    togglePause();

    pMenu.exec();
}

void MainWindow::on_buttonPause_toggled(bool checked)
{
    isPaused = !isPaused;
    pongGame->setPause(isPaused);
    ui->buttonPause->setText(isPaused ? "Wznów" : "Pauza");
}

void MainWindow::togglePause()
{
    isPaused = !isPaused;
    pongGame->setPause(isPaused);
    ui->buttonPause->setText(isPaused ? "Wznów" : "Pauza");
}

