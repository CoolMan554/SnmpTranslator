#ifndef DBLAYERBASE_H
#define DBLAYERBASE_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QTimeZone>
#include <QtSql>

class DbLayerBase : public QObject
{
    Q_OBJECT
public:
    explicit DbLayerBase(QObject *parent = nullptr);
    ~DbLayerBase();
    QString getDbHost() const { return DB_HOST; }
    int     getDbPort() const { return DB_PORT; }
    QString getDbName() const { return DB_NAME; }
    QString getDbUser() const { return DB_USER; }
    QString getDbPass() const { return DB_PASS; }
    QSqlDatabase getDb() const { return db; }
    bool isDbReady() const;
    void insertSqlCommand(const QString &data, const QDateTime curTimeEvent);
    bool ReconnectBase();
private:
    QSqlDatabase db;
    QString DB_HOST = QStringLiteral("127.0.0.1");
    int DB_PORT = 5432;
    QString DB_NAME = QStringLiteral("snmp");
    QString DB_USER = QStringLiteral("snmp");
    QString DB_PASS = QStringLiteral("snmp");
    void preparedQuery(const QString &queryStr, const QString &data, const QDateTime curTimeEvent);

signals:

};

#endif // DBLAYERBASE_H
