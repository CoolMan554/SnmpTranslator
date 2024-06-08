#include "snmptrapserver.h"

SnmpTrapServer::SnmpTrapServer(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);
    initSnmpParse();
    udpSocket->bind(QHostAddress::Any, 1162);    
    connect(udpSocket, &QUdpSocket::readyRead, this, &SnmpTrapServer::slotReadyRead);
    connect(snmpParseThread, &QThread::finished, snmpParseThread, &QThread::deleteLater);
    connect(this, &SnmpTrapServer::processTheDatagram, snmpParse, &SnmpParse::receivePacketSnmp, Qt::QueuedConnection);
}

SnmpTrapServer::~SnmpTrapServer()
{
    if(udpSocket)
    {
        udpSocket->close();
        delete udpSocket;
        udpSocket = nullptr;
    }
    if(snmpParse)
    {
        delete snmpParse;
        snmpParse = nullptr;
    }
    snmpParseThread->quit();
}

void SnmpTrapServer::initSnmpParse()
{
    snmpParse = new SnmpParse();
    snmpParseThread = new QThread();
    snmpParse->moveToThread(snmpParseThread);
    snmpParseThread->start();
}

void SnmpTrapServer::slotReadyRead()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        emit processTheDatagram(datagram);
    }
}
