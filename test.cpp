#include "test.h"
#include "ui_test.h"
#include "chart.h"

#include <QWidget>
#include <QVBoxLayout>

/**
* \file
* \brief Definicja metody klasy test
*
* Zawiera definicję metod klasy test.
*/

/**
 * @brief Konstruktor klasy test (testowanie połączenia).
 *
 * Tworzy obiekt dialogowy, inicjalizuje interfejs użytkownika do testowania połączenia i dodaje dwa wykresy typu `chart`
 * do obu używanych czujników z mikrokontrolera (acc - akcelerator, gyro-żyroskop).
 *
 * @param parent Wskaźnik do rodzica.
 */
test::test(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test)
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
}

/**
 * @brief Destruktor klasy test.
 *
 * Zwalnia pamięć zaalokowaną.
 */
test::~test()
{
    delete ui;
}
