#include "dblayerbase.h"

DbLayerBase::DbLayerBase(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(this->getDbHost());
    db.setDatabaseName(this->getDbName());
    db.setPort(this->getDbPort());
    db.setUserName(this->getDbName());
    db.setPassword(this->getDbPass());

    if(!db.open())
    {
        qDebug() << "DbLayerBase::" << db.lastError().text();
    }
    else qDebug() << "DbLayerBase:: Новое соединение СУБД" << db.connectionName();
}
DbLayerBase::~DbLayerBase()
{
    qDebug() << "DbLayerBase:: Соединение закрыто" << db.connectionName();
    db.close();
}

bool DbLayerBase::isDbReady() const
{
    return getDb().isOpen();
}

void DbLayerBase::insertSqlCommand(const QString &data, const QDateTime curTimeEvent)
{
    QString strCommand = QString("INSERT INTO event (eventin, additionalinfo) VALUES (:eventin, :additionalinfo)");
    preparedQuery(strCommand, data, curTimeEvent);
}

bool DbLayerBase::ReconnectBase()
{
    if(!db.open())
    {
        qDebug() << "ReconnectBase:: Нет соединения с базой" << db.lastError().text();
        return false;
    }
    return true;
}

void DbLayerBase::preparedQuery(const QString &queryStr, const QString &data, const QDateTime curTimeEvent)
{
    if(!isDbReady())
    {
        qDebug() << "DbLayerBase:: Нет соединения с базой" << db.lastError().text();
        if(!ReconnectBase())
            return;
    }
    QSqlQuery q(getDb());
    q.prepare(queryStr);
    q.bindValue(":eventin", curTimeEvent);
    q.bindValue(":additionalinfo", data);
    bool result = q.exec();

    if(!result)
    {
        qDebug() << "DbLayerBase::execQuery Ошибка в запросе " << q.lastError().text();
    }
}
