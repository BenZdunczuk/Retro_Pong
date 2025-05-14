#include "connection.h"
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <cstring>
#include <iostream>

/**
* \file
* \brief Plik connection.cpp
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
    : QObject{parent}
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
        std::cout << "Polaczono" << std::endl;
    } else {
        std::cout << "Blad polaczenia" << std::endl;
    }

    connect(&serial, &QSerialPort::readyRead, this, &connection::handleReadyRead);
}

    /**
     * @brief Metoda odbierająca dane z mikrokontrolera
     *
     * @return recievedData Dane odebrane z mikrokontrolera
     */
QByteArray connection::readData()
{
    QByteArray recievedData = serial.readAll();
    std::cout << "odebrano: " << recievedData.toStdString() << std::endl;
    return recievedData;
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
     * @brief Slot odbierający dane w momencie gotowości do odbierania danych
     */
void connection::handleReadyRead(){
    QByteArray data = serial.readAll();
    emit dataReceived(data);
}


// quint8 computeCRC8(quint8* pData, int Length, unsigned int Poly, quint8 InitVal)
// {
//     quint8 ResCRC = InitVal;

//     while (--Length >= 0) {
//         ResCRC ^= *pData++;
//         for (short int i=0; i < 8; ++i)
//             ResCRC = ResCRC & 0x80 ? (ResCRC << 1) ^ Poly : ResCRC << 1;
//     }
//     return ResCRC & 0xFF;
// }

// void TestCRC8(const char* pData, unsigned int Poly, unsigned short int InitVal)
// {
//     const unsigned int Len   = strlen(pData);
//     unsigned char *pDataBuff = new unsigned char[Len+1];

//     memcpy(pDataBuff,pData,Len);

//     unsigned short int CRC8;

//     CRC8 = ComputeCRC8(pDataBuff,Len,Poly,InitVal);

//     cout << endl
//          << "-- Test CRC8 ------" << endl
//          << " Wynik obliczenia -> CRC8 = " << hex << CRC8 << endl;


//     pDataBuff[Len] = CRC8;
//     CRC8 = ComputeCRC8(pDataBuff,Len+1,Poly,InitVal);

//     cout << "  Po dodaniu CRC8 -> CRC8 = " << CRC8 << endl << endl;

//     delete pDataBuff;
// }

// void connection::sendData(QString &data)
// {
//     if (serial.isOpen()) {
//         QByteArray base = data.toUtf8();
//         quint8 crc = computeCRC8(base,1,1,1);
//         QString full = QString("%1*%2\n").arg(QString(base)).arg(crc, 2, 16, QLatin1Char('0')).toUpper();
//         serial.write(full.toUtf8());
//     }
// }


