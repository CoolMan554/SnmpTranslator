#include "snmptrapserver.h"

SnmpTrapServer::SnmpTrapServer(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);
    initSnmpParse();
    udpSocket->bind(QHostAddress::Any, 1162);
    udpSocket->setSocketOption(QAbstractSocket::SocketOption::ReceiveBufferSizeSocketOption, 26214400);//Выделяем 50Мб буфера для принятие пакетов
    connect(this, &SnmpTrapServer::Reconnect, [this]()
    {
        udpSocket->bind(QHostAddress::Any, 1162);
        QTimer::singleShot(periodReconnect * 1000, this, &SnmpTrapServer::checkUdpSocket);
    });
    connect(udpSocket, &QUdpSocket::readyRead, this, &SnmpTrapServer::slotReadyRead);
    connect(snmpParseThread, &QThread::finished, snmpParseThread, &QThread::deleteLater);
    connect(this, &SnmpTrapServer::processTheDatagram, snmpParse, &SnmpParse::receivePacketSnmp, Qt::QueuedConnection);
    checkUdpSocket();
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

void SnmpTrapServer::checkUdpSocket()
{
    if(udpSocket->state() == QAbstractSocket::BoundState)
        qDebug() << "SnmpTrapServer" << "The socket on port 1162 has been successfully opened";
    else
    {
        qDebug() << "SnmpTrapServer" << "Failed to open socket on port 1162. Retry after 10 seconds...";
        emit Reconnect();
    }
}

void SnmpTrapServer::slotReadyRead()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        emit processTheDatagram(datagram);
    }
}
