#include "connection.h"
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <cstring>
#include <iostream>

/**
* \file
* \brief Definicja metody klasy connection
*
* Zawiera definicję protokołu komunikacji
*/

#define portName "COM4"

    /**
     * @brief Konstruktor klasy connection
     *
     * @param[in] Opcjonalny wskaźnik do rodzica
     */
connection::connection(QObject *parent)
    : QObject{parent}, isConnected(false)
{
    //start();
}

    /**
     * @brief Destruktor klasy connection
     */
connection::~connection(){
    stop();
}

    /**
     * @brief Slot inicjalizujący połączenie po USB
     *
     * @param[out] serial Zmienna reprezentująca skonfigurowane połączenie
     */
void connection::start(){
    serial.setPortName(portName);
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (serial.open(QIODevice::ReadWrite)) {
        // std::cout << "Polaczono" << std::endl;
        connect(&serial, &QSerialPort::readyRead, this, &connection::handleReadyRead);
        isConnected = true;
    } else {
        // std::cout << "Blad polaczenia" << std::endl;
        isConnected = false;
    }
}

    /**
     * @brief Slot kończący połączenie po USB
     *
     * @param[out] serial Zmienna reprezentująca zamknięte połączenie
     */
void connection::stop() {
    if (serial.isOpen()) {
        serial.close();
    }
}

    /**
     * @brief Metoda typu getter umożliwiająca dostęp do atrybutu isConnected;
     *
     * @return isConnected Zmienna boolowska reprezentująca status połączenia (0 - brak połączenia, 1 - połączenie aktywne)
     */
bool connection::getConnectionStatus(){
    return isConnected;
}

    /**
     * @brief Slot odbierający dane w momencie gotowości do odbierania danych
     */
void connection::handleReadyRead(){
    QByteArray data = serial.readAll();
    emit dataReceived(data);
}

    /**
     * @brief Metoda obrabiająca surowe dane
     *
     * Metoda obrabia surowe dane w postaci tablicy bajtów
     * i zwraca dane poprzez sygnał dataProcessed() w postaci liczbowej w rozróżnieniu na osie X,Y i Z.
     *
     * @param[in] dataRaw dane odebrane bezpośrednio z czujnika
     */
void connection::processData(const QByteArray dataRaw){
    QString gyroData[3], accData[3];

    QString data = QString::fromUtf8(dataRaw);
    QStringList dataSplit = data.split('\n');

    for(int i=0;i<dataSplit.size();++i){
        QStringList segment = dataSplit[i].split(';');

        if (segment.size() == 3) {
            accData[0] = segment[0];
            accData[1] = segment[1];
            accData[2] = segment[2];
            QStringList acc;
            for (int i = 0; i < 3; ++i) {
                acc << accData[i];
            }
            emit dataProcessed(acc);
        }
    }
}


    /**
     * @brief Metoda obliczająca sumę kontrolną wiadomości przychodzących z mikrokontrolera
     *
     * @param[in] data część transmisji z mikrokontrolera, którą stanowią dane z czujników
     * @return resCRC zakodowana suma kontrolna
     *
     * Wykorzystuje algorytm CRC8, w którym używany wielomian to x^8 + x^2 + x + 1
     */
quint8 connection::computeCRC8(const QByteArray& data){
    quint8 resCRC = 0x00;
    quint8 poly = 0x07;

    for (int i = 0; i < data.size(); ++i) {
        resCRC ^= static_cast<quint8>(data[i]);
        for (int bit = 0; bit < 8; ++bit) {
            if (resCRC & 0x80)
                resCRC = ((resCRC << 1) ^ poly) & 0xFF;
            else
                resCRC = (resCRC << 1) & 0xFF;
        }
    }
    return resCRC;
}

    /**
     * @brief Metoda porównująca sumę kontrolną uzyskaną z transmisji z obliczoną
     *
     * @param[in] receivedDataWithCRC cała wiadomość odebrana z mikrokontrolera
     * @return true jeśli obliczone CRC są identyczne, false jeśli występuje błąd w transmisji
     *
     * Wykorzystuje algorytm CRC8, w którym używany wielomian to x^8 + x^2 + x + 1
     */
bool connection::verifyCRC8(const QByteArray& receivedDataWithCRC){
    if(receivedDataWithCRC.size() < 2){return false;} //jeśli nie ma części z sumą kontrolną

    QByteArray data = receivedDataWithCRC.left(receivedDataWithCRC.size() - 1); //oderwanie z wiadomości części z sumą kontrolną

    return (computeCRC8(data) == static_cast<quint8>(receivedDataWithCRC.back()));
}
