#ifndef SNMPPARSE_H
#define SNMPPARSE_H

#include <QObject>
#include <QNetworkDatagram>
#include <QDebug>
#include <QMutex>
#include "dblayerbase.h"

class SnmpParse : public QObject
{
    Q_OBJECT
public:
    explicit SnmpParse(QObject *parent = nullptr);
    ~SnmpParse();

public slots:
    void receivePacketSnmp(const QNetworkDatagram datagram);
    void initDataBase();
private:
    DbLayerBase *dbLayer{};
    QMutex *mutex{};

signals:

};

#endif // SNMPPARSE_H
