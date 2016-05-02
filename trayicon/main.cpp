#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <QMessageBox>
#include <QVariant>
#include "model.h"
#include "trayicon.h"

// This is bad but we need the rootObject from e.g. model.cpp which otherwise has no access
QObject *rootObject = NULL;


Q_DECLARE_METATYPE(QSystemTrayIcon::ActivationReason)

int main(int argc, char *argv[])
{
    qmlRegisterType<Model>("Model", 1,0, "Model");

    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    rootObject = engine.rootObjects().at(0);
    TrayIcon trayicon(rootObject);

    return app.exec();
}
