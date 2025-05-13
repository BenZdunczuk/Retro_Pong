#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QDialog>
#include <QWidget>
#include <QMainWindow>

class connection : public QObject
{
    Q_OBJECT
public:
    explicit connection(QObject *parent = nullptr);
    ~connection();
    void sendData(QString &data);

public slots:
    QByteArray readData();
    void start();
    void stop();

private slots:
    void handleReadyRead();

private:
    QSerialPort serial;

signals:
    void dataReceived(const QByteArray &data);
};

#endif // CONNECTION_H
