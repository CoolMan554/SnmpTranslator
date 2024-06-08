#ifndef SNMPTRAPSERVER_H
#define SNMPTRAPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QThread>
#include "snmpparse.h"

class SnmpTrapServer : public QObject
{
    Q_OBJECT
public:
    explicit SnmpTrapServer(QObject *parent = nullptr);
    ~SnmpTrapServer();
private:
    QUdpSocket *udpSocket{};
    SnmpParse *snmpParse{};
    QThread *snmpParseThread{};
    void initSnmpParse();

private slots:
    void slotReadyRead();


signals:
    void processTheDatagram(const QNetworkDatagram datagram);
};

#endif // SNMPTRAPSERVER_H
