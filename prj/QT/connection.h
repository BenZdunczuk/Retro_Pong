#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QDialog>
#include <QWidget>
#include <QMainWindow>

/**
* \file
* \brief Definicja metody klasy connection
*
* Zawiera definicję klasy connection i jej metod. Odpowiada za połączenie z mikrokontrolerem poprzez USB
*/

/**
 * @brief Klasa connection reprezentuje połączenie pomiędzy aplikacją w QT a mikrokontrolerem STM
 *
 * Zawiera interfejs USB do dwustronnej komunikacji
 */
class connection : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor klasy connection
     */
    explicit connection(QObject *parent = nullptr);

    /**
     * @brief Destruktor klasy connection
     */
    ~connection();

    /**
     * @brief Metoda wysyłająca dane do mikrokontrolera
     */
    void sendData(QString &data);

public slots:
    /**
     * @brief Metoda odbierająca dane z mikrokontrolera
     */
    QByteArray readData();

    /**
     * @brief Slot inicjalizujący połączenie po USB
     */
    void start();

    /**
     * @brief Slot kończący połączenie po USB
     */
    void stop();

private slots:
    /**
     * @brief Slot odbierający dane w momencie gotowości do odbierania danych
     */
    void handleReadyRead();

private:
    /**
     * @brief Zmienna reprezentująca połączenie przez USB
     */
    QSerialPort serial;

signals:
    /**
     * @brief Sygnał wysyłany w momencie odebrania danych, przechowujący odebrane dane
     */
    void dataReceived(const QByteArray &data);
};

#endif // CONNECTION_H
