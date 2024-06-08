#ifndef SNMPPARSE_H
#define SNMPPARSE_H

#include <QObject>
#include <QNetworkDatagram>
#include <QDebug>

class SnmpParse : public QObject
{
    Q_OBJECT
public:
    explicit SnmpParse(QObject *parent = nullptr);

public slots:
    void receivePacketSnmp(const QNetworkDatagram datagram);

signals:

};

#endif // SNMPPARSE_H
