#ifndef TEST_H
#define TEST_H

#include "connection.h"
#include "ui_test.h"

#include <QObject>
#include <QWidget>
#include <QDialog>

/**
* \file
* \brief Definicja metody klasy test
*
* Zawiera definicję metod klasy test.
*/

namespace Ui {
/**
 * @brief Przestrzeń nazw Ui zawiera deklaracje klas UI wygenerowanych przez Qt Designer.
 */
class test;
}

/**
 * @brief Klasa test reprezentuje okno dialogowe z reprezentacją danych z czujników.
 *
 * Klasa dziedziczy po QDialog i stanowi interfejs graficzny, w którym można
 * umieścić dynamicznie generowane wykresy typu `chart`. Wykorzystywana do
 * prezentacji danych dostarczonych przez czujniki w postaci graficznej oraz liczbowej.
 */
class test : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Konstruktor klasy test.
     */
    explicit test(QWidget *parent = nullptr,connection *connect = nullptr);

    /**
     * @brief Destruktor klasy test.
     */
    ~test();

    connection* connectTest;



private slots:
    /**
     * @brief Slot wyświetlający dane numeryczne z sensorów w okienku test
     */
    void displayData(bool sensor, QStringList data);

private:
    /**
     * @brief Wskaźnik do obiektu interfejsu użytkownika wygenerowanego przez Qt Designer.
     */
    Ui::test *ui;
};

#endif // TEST_H
