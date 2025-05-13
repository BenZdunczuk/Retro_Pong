#ifndef CHART_H
#define CHART_H

#include <QWidget>

/**
* \file
* \brief Definicja metody klasy chart
*
* Zawiera definicję metod klasy chart.
*/

/**
 * @brief Klasa chart reprezentuje wykresy używane do wizualizacji danych
 *
 * Zawiera definicję widgetu rysującego wykres na podstawie danych odebranych z mikrokontrolera.
 */
class chart : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy chart.
     * @param parent Opcjonalny wskaźnik do rodzica.
     * @param setPhase Przesunięcie fazowe sinusa (tylko w wersji do testowania wyświetlania wykresu)
     */
    explicit chart(QWidget *parent = nullptr,double setPhase = 0.0);

protected:
    /**
     * @brief Metoda inicjalizująca rysowanie wykresu
     * @param event Opcjonalny wskaźnik do rysowania.
     */
    void paintEvent(QPaintEvent *event) override;

private slots:
    /**
     * @brief Slot odpoweidzialny za przesuwanie wykresu w czasie
     */
    void onTimeout();

private:
    /**
     * @brief Zmienna określająca przesunięcie fazowe
     */
    double phase;

signals:
};

#endif // CHART_H
