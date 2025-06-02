#include "test.h"
#include "chart.h"

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
    : QDialog(parent), ui(new Ui::test), connectTest(connect)
{
    ui->setupUi(this);

    chart *wykresAcc = new chart(ui->chartAcc);
    QVBoxLayout *layout = new QVBoxLayout(ui->chartAcc);
    layout->addWidget(wykresAcc);

    chart *wykresGyro= new chart(ui->chartGyro);
    QVBoxLayout *layout2 = new QVBoxLayout(ui->chartGyro);
    layout2->addWidget(wykresGyro);

    if(connectTest->getConnectionStatus()){
        ui->connectionStatus->setText("online");
    }else{
        ui->connectionStatus->setText("offline");
    }

    QObject::connect(connectTest,&connection::dataProcessed,this,&test::displayData);
    QObject::connect(connectTest,&connection::dataProcessed,wykresAcc, &chart::onNewData);
    QObject::connect(connectTest,&connection::dataProcessed,wykresGyro, &chart::onNewData);
}

/**
 * @brief Destruktor klasy test.
 *
 * Odpowiada za zwolnienie pamięci alokowanej oraz zamyka okienko.
 */
test::~test()
{
    delete ui;
}

/**
 * @brief Slot wyświetlający dane numeryczne z sensorów w okienku test
 *
 * Odbiera sygnał z klasy connection z przetworzonymi danymi z czujników i wyświetla je w lineEditach w okienku test
 */
void test::displayData(bool sensor, QStringList data){
    if(sensor){             //jeśli to akcelerometr
        ui->accX->setText(data[0]);
        ui->accY->setText(data[1]);
        ui->accZ->setText(data[2]);
    }
    else if(!sensor){        //jeśli to żyroskop
        ui->gyroX->setText(data[0]);
        ui->gyroY->setText(data[1]);
        ui->gyroZ->setText(data[2]);
    }
}
