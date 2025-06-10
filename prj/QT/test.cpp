#include "test.h"
#include "chart.h"
#include "menu.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QThread>
#include <QDebug>
// #include <iostream>

/**
* \file
* \brief Definicja metody klasy test
*
* Zawiera definicję metod klasy test.
*/

/**
 * @brief Konstruktor klasy test.
 *
 * Tworzy obiekt dialogowy, inicjalizuje interfejs użytkownika do testowania połączenia i dodaje dwa wykresy typu `chart`
 * do obu używanych czujników z mikrokontrolera (acc - akcelerator, gyro-żyroskop).
 *
 * @param parent Wskaźnik do rodzica.
 */
test::test(QWidget *parent,connection* connect)
    : QDialog(parent), ui(new Ui::test), connectTest(connect), pMenu(nullptr)
{
    ui->setupUi(this);

    chart *wykresAcc = new chart(ui->chartAcc);
    QVBoxLayout *layout = new QVBoxLayout(ui->chartAcc);
    layout->addWidget(wykresAcc);

    if(connectTest->getConnectionStatus()){
        ui->connectionStatus->setText(tr("połączono"));
    }else{
        ui->connectionStatus->setText(tr("brak połączenia"));
    }

    QObject::connect(connectTest,&connection::dataProcessed,this,&test::displayData);
    QObject::connect(connectTest,&connection::dataProcessed,wykresAcc, &chart::onNewData);
}

/**
 * @brief Destruktor klasy test.
 *
 * Odpowiada za zwolnienie pamięci alokowanej oraz zamyka okienko.
 */
test::~test()
{
    emit testExitSignal();
    delete ui;
}

/**
 * @brief Slot wyświetlający dane numeryczne z sensorów w okienku test
 *
 * Odbiera sygnał z klasy connection z przetworzonymi danymi z czujników i wyświetla je w lineEditach w okienku test
 */
void test::displayData(QStringList data){
    ui->accX->setText(data[0]);
    ui->accY->setText(data[1]);
    ui->accZ->setText(data[2]);
}

/**
 * @brief Slot zamykający okno po naciśnięciu przycisku Wyjdź
 *
 * Powoduje zamknięcie okienka testowania połączenia
 */
void test::on_pushButton_clicked()
{
    closeTest();
}

/**
 * @brief Metoda zamykająca okno
 *
 * Powoduje zamknięcie okienka testowania połączenia oraz wysłanie sygnału o zamknięciu
 */
void test::closeTest(){
    emit testExitSignal();
    test::close();
}

    /**
     * @brief Metoda obsługująca tłumaczenie ui okna klasy
     *
     * Uruchomiana podczas zmiany języka w menu aplikacji
     */
void test::reTranslate(){
    ui->retranslateUi(this);
}

    /**
     * @brief Metoda reagująca na zamknięcie okna
     *
     * Reaguje na manualne zamknięcie okna przyciskiem w prawym górnym kącie okna
     */
void test::closeEvent(QCloseEvent *event) {
    emit testExitSignal();
    event->accept();
}

