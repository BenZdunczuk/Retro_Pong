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

    // /**
    //  * @brief Metoda wysyłająca dane do mikrokontrolera
    //  */
    // void sendData(QString &data);

    /**
     * @brief Metoda typu getter umożliwiająca dostęp do atrybutu isConnected;
     */
    bool getConnectionStatus();

public slots:
    // /**
    //  * @brief Metoda odbierająca dane z mikrokontrolera
    //  */
    // QByteArray readData();

    /**
     * @brief Slot inicjalizujący połączenie po USB
     */
    void start();

    /**
     * @brief Slot kończący połączenie po USB
     */
    void stop();

    void processData(const QByteArray data);

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

    void dataProcessed(int sensorType,QStringList dataProcessed);
};

#endif // CONNECTION_H
