#include "snmptrapserver.h"

SnmpTrapServer::SnmpTrapServer(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 1162);
    connect(udpSocket, &QUdpSocket::readyRead, this, &SnmpTrapServer::slotReadyRead);
}

SnmpTrapServer::~SnmpTrapServer()
{
    if(udpSocket)
    {
        delete udpSocket;
        udpSocket = nullptr;
    }
}

void SnmpTrapServer::slotReadyRead()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
    }
}
