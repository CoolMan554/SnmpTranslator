#include "snmpparse.h"

SnmpParse::SnmpParse(QObject *parent)
    : QObject{parent}
{

}

SnmpParse::~SnmpParse()
{
    if(mutex)
    {
        delete mutex;
        mutex = nullptr;
    }
    if(dbLayer)
    {
        delete dbLayer;
        dbLayer = nullptr;
    }
}

void SnmpParse::receivePacketSnmp(const QNetworkDatagram datagram)
{
    QMutexLocker locker(mutex);
    quint32 ipv4 = datagram.senderAddress().toIPv4Address();
    QHostAddress address = QHostAddress(ipv4);
    qDebug() << "SnmpParse::receivePacketSnmp Address" << address << "Port:" << datagram.senderPort() << datagram.data();
    if(dbLayer)
    {
        dbLayer->insertSqlCommand(datagram.data());//Добавление записи в базу
    }
}

void SnmpParse::initDataBase()
{
    mutex = new QMutex();
    dbLayer = new DbLayerBase();
}
