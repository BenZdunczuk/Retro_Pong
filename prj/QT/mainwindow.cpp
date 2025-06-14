#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include "ponging.h"
#include "test.h"
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
     * @param[in] parent Opcjonalny wskaźnik do rodzica.
     */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), isPaused(false), isTestOpen(false), pTest(nullptr), pMenu(nullptr)
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
            //qDebug() << "Odebrano:" << data.toStdString();
            connectMain->processData(data);
        } else {
            qDebug() << "zle crc";
        }
    });
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, connectMain, &connection::stop);

    thread->start();

    pMenu = new menu(this, connectMain);
    // pMenu->show();
    on_buttonPause_clicked();
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
    if(pTest != nullptr) pTest->close();

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
    pMenu->show();
    ui->buttonPause->setText(tr("Zatrzymano grę"));
    ui->buttonPause->setEnabled(false);
}

    /**
     * @brief Przełącza stan gry (pomiędzy stanami: gra włączona i zatrzymana).
     */
void MainWindow::togglePause()
{
    isPaused = !isPaused;
    pongGame->setPause(isPaused);
}

    /**
     * @brief Zmienna stan logiczny zmiennej informującej o otwartym oknie testu
     */
void MainWindow::toggleTestOpen()
{
    isTestOpen = !isTestOpen;
}

    /**
     * @brief Slot wznawiający grę
     *
     * Odbiera sygnał z klasy menu i wysyła sygnał do klasy widgetu gry Pong
     */
void MainWindow::resumedGame(){
    unlockPauseButton();
    emit resumed();
}

    /**
     * @brief Metoda typu getter zwracająca wartość zmiennej isTestOpen
     */
bool MainWindow::getTestOpen(){
    return isTestOpen;
}

    /**
     * @brief Slot resetujący grę
     *
     * Odbiera sygnał z klasy menu i wysyła sygnał do klasy widgetu gry Pong
     */
void MainWindow::restartedGame(){
    unlockPauseButton();
    emit restarted();
}

    /**
     * @brief Slot obsługujący zamknięcie okna test
     *
     *  Slot jest uruchamiany w odpowiedzi na zamknięcie okna testu
     */
void MainWindow::testClosed(){
    toggleTestOpen();
    pMenu->unlockTestButton();
    pTest = nullptr;
}

    /**
     * @brief Slot otwierający okienko testu
     *
     *  Slot jest wywoływany z klasy menu, tworzy i inicjalizuje klasę monitora połączenia,
     *  zmienia zmienną informującą o stanie okna monitora połączenia oraz łączy slot zamknięcia okna monitora połączenia
     *  z sygnałem wysyłanym z monitora połączenia
     *
     */
void MainWindow::openTest(){
    pTest = new test(this,connectMain);
    pTest->show();
    toggleTestOpen();
    connect(pTest,&test::testExitSignal,this,&MainWindow::testClosed);
}

    /**
     * @brief Slot odblokowujący przycisk pauzy
     *
     *  Wykonywany w momencie wznowienia gry w menu, pozwala na ponowne zatrzymanie i otworzenie menu
     */
void MainWindow::unlockPauseButton(){
    ui->buttonPause->setEnabled(true);
    ui->buttonPause->setText(tr("Pauza"));
}

    /**
     * @brief Metoda zmieniająca język całej aplikacji
     *
     *  Wykonywana w momencie przełączenia języka aplikacji w menu, wczytuje nowy plik z tłumaczeniem
     *
     *  @param[in] languageCode kod języka, pl_PL - polski, en_US - angielski
     *
     */
void MainWindow::switchLanguage(const QString &languageCode) {
    qApp->removeTranslator(translatorMainWindow);

    translatorMainWindow = new QTranslator(this);

    if (translatorMainWindow->load("pong_" + languageCode + ".qm"))
    qApp->installTranslator(translatorMainWindow);

    ui->retranslateUi(this);
    pMenu->reTranslate();
    if(pTest != nullptr) pTest->reTranslate();
}

    /**
     * @brief Metoda typu setter ustawiająca obiekt tłumacza
     *
     *  @param[in] newTranslator wskaźnik do nowego obiektu tłumacza
     */
void MainWindow::setTranslator(QTranslator *newTranslator){
    translatorMainWindow = newTranslator;
}
