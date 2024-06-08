#include <QCoreApplication>
#include <QDebug>
#include <memory>
#include "snmptrapserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    int errorCode = 0;

    try
    {
        std::shared_ptr<SnmpTrapServer> snmpTrapServer = std::make_shared<SnmpTrapServer>();
        errorCode = app.exec();
        qCritical() << "Critical SnmpTrapServer Error";
    }
    catch (const std::exception &ex)
    {
        qCritical() << "Exception SnmpTrapServer Error" << ex.what();
    }
    catch(...)
    {
        qCritical() << "Unknown Exception";
    }

    return errorCode;
}
