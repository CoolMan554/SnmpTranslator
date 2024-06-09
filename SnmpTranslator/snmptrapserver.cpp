#include "snmptrapserver.h"

quint32 SnmpTrapServer::countSuccessTraps {0};

SnmpTrapServer::SnmpTrapServer(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);
    initSnmpParse();
    udpSocket->bind(QHostAddress::Any, 1162);
    udpSocket->setSocketOption(QAbstractSocket::SocketOption::ReceiveBufferSizeSocketOption, 262144000);//Выделяем 500Мб буфера для принятие пакетов
    connect(this, &SnmpTrapServer::Reconnect, [this]()
    {
        udpSocket->bind(QHostAddress::Any, 1162);
        udpSocket->setSocketOption(QAbstractSocket::SocketOption::ReceiveBufferSizeSocketOption, 262144000);//Выделяем 500Мб буфера для принятие пакетов
        QTimer::singleShot(periodReconnect * 1000, this, &SnmpTrapServer::checkUdpSocket);
    });
    connect(udpSocket, &QAbstractSocket::errorOccurred, this, &SnmpTrapServer::ServerSocketError);
    connect(udpSocket, &QUdpSocket::readyRead, this, &SnmpTrapServer::slotReadyRead);
    connect(snmpParseThread, &QThread::finished, snmpParseThread, &QThread::deleteLater);
    connect(snmpParseThread, &QThread::started, snmpParse, &SnmpParse::initDataBase);
    connect(this, &SnmpTrapServer::processTheDatagram, snmpParse, &SnmpParse::receivePacketSnmp, Qt::QueuedConnection);
    snmpParseThread->start();
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
    snmpParseThread->setObjectName("SnmpParse");
    snmpParse->moveToThread(snmpParseThread);
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
        const QNetworkDatagram datagram = udpSocket->receiveDatagram();
        qDebug() << "SnmpTrapServer::slotReadyRead::countSuccessTraps::" << ++countSuccessTraps;
        emit processTheDatagram(datagram);
    }
}

void SnmpTrapServer::ServerSocketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "SnmpTrapServer::ServerSocketError" << socketError;
}
