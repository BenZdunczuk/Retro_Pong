#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include "ponging.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QThread>

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

    connectMain = new connection;

    pongGame = new PongWidget(ui->gameWidget,connectMain);
    QVBoxLayout *layout = new QVBoxLayout(ui->gameWidget);
    layout->addWidget(pongGame);

    pongGame->mainWindow = this;

        //połączenie z czujnikami
    QThread *thread = new QThread;

    connectMain->moveToThread(thread);

    QObject::connect(thread, &QThread::started, connectMain, &connection::start);
    QObject::connect(connectMain, &connection::dataReceived, [this](const QByteArray &dataRaw) {
        if(connectMain->verifyCRC8(dataRaw)){
            QByteArray data = dataRaw;
            data.chop(1);
            qDebug() << "Odebrano:" << data.toStdString();
            connectMain->processData(data);
        } else {
            qDebug() << "zle crc";
        }
    });
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, connectMain, &connection::stop);

    thread->start();
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
    menu pMenu(this, connectMain);
    pMenu.exec();

}

    /**
     * @brief Przełącza stan gry (pomiędzy stanami: gra włączona i zatrzymana).
     */
void MainWindow::togglePause()
{
    isPaused = !isPaused;
    pongGame->setPause(isPaused);
    ui->buttonPause->setText(isPaused ? "Wznów" : "Pauza");
}

    /**
     * @brief Slot wznawiający grę
     *
     * Odbiera sygnał z klasy menu i wysyła sygnał do klasy widgetu gry Pong
     */
void MainWindow::resumedGame(){
    emit resumed();
}

/**
     * @brief Slot restartujący grę
     *
     * Odbiera sygnał z klasy menu i wysyła sygnał do klasy widgetu gry Pong
     */
void MainWindow::restartedGame(){
    emit restarted();
}
