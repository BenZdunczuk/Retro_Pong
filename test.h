#ifndef TEST_H
#define TEST_H

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
     *
     * Inicjalizuje interfejs użytkownika oraz ustawia widżety i układy.
     *
     * @param parent Wskaźnik do obiektu rodzica.
     */
    explicit test(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy test.
     *
     * Odpowiada za zwolnienie pamięci alokowanej.
     */
    ~test();

private slots:

private:
    /**
     * @brief Wskaźnik do obiektu interfejsu użytkownika wygenerowanego przez Qt Designer.
     */
    Ui::test *ui;
};

#endif // TEST_H
