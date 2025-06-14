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
     * @brief Metoda typu getter umożliwiająca dostęp do atrybutu isConnected;
     */
    bool getConnectionStatus();

public slots:

    /**
     * @brief Slot inicjalizujący połączenie po USB
     */
    void start();

    /**
     * @brief Slot kończący połączenie po USB
     */
    void stop();

    /**
     * @brief Metoda obrabiająca surowe dane
     */
    void processData(const QByteArray data);

    /**
     * @brief Metoda obliczająca sumę kontrolną wiadomości przychodzących z mikrokontrolera
     */
    quint8 computeCRC8(const QByteArray& data);

    /**
     * @brief Metoda porównująca sumę kontrolną uzyskaną z transmisji z obliczoną
     */
    bool verifyCRC8(const QByteArray& receivedDataWithCRC);

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

    /**
     * @brief Zmienna boolowska reprezentująca status połączenia (0 - brak połączenia, 1 - połączenie aktywne)
     */
    bool isConnected;

signals:
    /**
     * @brief Sygnał wysyłany w momencie odebrania danych, przechowujący odebrane dane
     */
    void dataReceived(const QByteArray &data);

    /**
     * @brief Sygnał wysyłany w po obrobieniu danych, przechowujący informacje o typie czujnika oraz dane z podziałem na osie
     */
    void dataProcessed(QStringList dataProcessed);
};

#endif // CONNECTION_H
