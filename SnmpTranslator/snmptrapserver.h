#ifndef SNMPTRAPSERVER_H
#define SNMPTRAPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

class SnmpTrapServer : public QObject
{
    Q_OBJECT
public:
    explicit SnmpTrapServer(QObject *parent = nullptr);
    ~SnmpTrapServer();
private:
    QUdpSocket *udpSocket{};

private slots:
    void slotReadyRead();


signals:

};

#endif // SNMPTRAPSERVER_H
