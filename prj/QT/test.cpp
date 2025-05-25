#include "test.h"
#include "chart.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QThread>
#include <QDebug>
#include <iostream>

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
    // chart *wykres = new chart(ui->chartWidget);
    // wykres->show();

    ui->setupUi(this);

    chart *wykres = new chart(ui->chartAcc);
    QVBoxLayout *layout = new QVBoxLayout(ui->chartAcc);
    layout->addWidget(wykres);

    chart *wykres2 = new chart(ui->chartGyro,10);
    QVBoxLayout *layout2 = new QVBoxLayout(ui->chartGyro);
    layout2->addWidget(wykres2);

    if(connectTest->getConnectionStatus()){
        ui->connectionStatus->setText("online");
    }else{
        ui->connectionStatus->setText("offline");
    }

    QObject::connect(connectTest,&connection::dataProcessed,this,&test::displayData);
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

bool test::displayData(bool sensor, QStringList data){
    if(sensor){
        ui->accX->setText(data[0]);
        ui->accY->setText(data[1]);
        ui->accZ->setText(data[2]);
        qDebug() << "accX: " << data[0];
        return 0;
    }
    else if(!sensor){
        ui->gyroX->setText(data[0]);
        ui->gyroY->setText(data[1]);
        ui->gyroZ->setText(data[2]);
        return 0;
    }
    return 1;
}
