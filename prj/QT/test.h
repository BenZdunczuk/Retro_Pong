#ifndef TEST_H
#define TEST_H

#include "connection.h"
#include "ui_test.h"
// #include "mainwindow.h"

#include <QObject>
#include <QWidget>
#include <QDialog>

/**
* \file
* \brief Definicja metody klasy test
*
* Zawiera definicję metod klasy test.
*/

class menu;

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

    /**
     * @brief Wskaźnik do obiektu połączenia z mikroprocesorem
     */
    connection* connectTest;

    /**
     * @brief Metoda zamykająca okienko testu
     */
    void closeTest();

    /**
     * @brief Metoda obsługująca tłumaczenie ui okna klasy
     */
    void reTranslate();

private slots:
    /**
     * @brief Slot wyświetlający dane numeryczne z sensorów w okienku test
     */
    void displayData(QStringList data);

    /**
     * @brief Slot zamykający okno
     */
    void on_pushButton_clicked();

private:
    /**
     * @brief Wskaźnik do obiektu interfejsu użytkownika wygenerowanego przez Qt Designer.
     */
    Ui::test *ui;

    /**
     * @brief Wskaźnik do obiektu menu.
     */
    menu *pMenu;

    /**
     * @brief Metoda reagująca na zamknięcie okna
     */
    void closeEvent(QCloseEvent *event) override;

signals:
    /**
     * @brief Sygnał wysyłany w momencie zamknięcia okna
     */
    void testExitSignal();
};

#endif // TEST_H
