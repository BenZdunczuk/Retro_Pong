// #include "connection.h"
// #include <QtSerialPort/QSerialPort>
// #include <QDebug>

// #define portName "COM4"

// connection::connection(QObject *parent)
//     : QObject{parent}
// {
//     serial.setPortName(portName);
//     serial.setBaudRate(QSerialPort::Baud115200);
//     serial.setDataBits(QSerialPort::Data8);
//     serial.setParity(QSerialPort::NoParity);
//     serial.setStopBits(QSerialPort::OneStop);
//     serial.setFlowControl(QSerialPort::NoFlowControl);

//     if (serial.open(QIODevice::ReadWrite)) {
//         qDebug() << "Połączono";
//         connect(&serial, &QSerialPort::readyRead, this, &connection::readData);
//     } else {
//         qDebug() << "Błąd połączenia" << serial.errorString();
//     }
// }

// QByteArray connection::readData()
// {
//     QByteArray recievedData = serial.readAll();
//     qDebug() << recievedData;
//     return recievedData;
// }

// /**
//  * @brief Oblicza sumę kontrolną CRC-8 dla podanych danych.
//  *
//  * Funkcja implementuje algorytm CRC-8 z wielomianem 0x07 (x⁸ + x² + x + 1),
//  * bez refleksji i bez inwersji końcowej. Używana do sprawdzania integralności danych
//  * przesyłanych np. przez UART między mikrokontrolerem a komputerem.
//  *
//  * @param data Wskaźnik do tablicy bajtów wejściowych.
//  * @param len Liczba bajtów do przetworzenia.
//  * @return uint8_t Obliczona suma CRC (8-bitowa).
//  */
// quint8 computeCRC8(QByteArray &data)
// {
//     quint8 crc = 0x00;
//     for (char b : data) {
//         crc ^= static_cast<quint8>(b);
//         for (int i = 0; i < 8; ++i) {
//             if (crc & 0x80)
//                 crc = (crc << 1) ^ 0x07;
//             else
//                 crc <<= 1;
//         }
//     }
//     return crc;
// }

// void connection::sendData(QString &data)
// {
//     if (serial.isOpen()) {
//         QByteArray base = data.toUtf8();
//         quint8 crc = computeCRC8(base);
//         QString full = QString("%1*%2\n").arg(QString(base)).arg(crc, 2, 16, QLatin1Char('0')).toUpper();
//         serial.write(full.toUtf8());
//     }
// }


