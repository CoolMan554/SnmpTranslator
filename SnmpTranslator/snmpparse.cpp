#include "snmpparse.h"

SnmpParse::SnmpParse(QObject *parent)
    : QObject{parent}
{

}

void SnmpParse::receivePacketSnmp(const QNetworkDatagram datagram)
{
    qDebug() << "SnmpParse::receivePacketSnmp Address" << datagram.senderAddress() << "Port:" << datagram.senderPort();
}
