#include <QApplication>
#include <QAction>
#include <QMenu>
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


        // Check if we have SysTray support
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Main"),
                                 QObject::tr("This application requires system tray support."));
        return 1;
    }

    rootObject = engine.rootObjects().at(0);

    QAction *minimizeAction = new QAction(QObject::tr("Mi&nimize"), rootObject);
    rootObject->connect(minimizeAction, SIGNAL(triggered()), rootObject, SLOT(hide()));
    QAction *restoreAction = new QAction(QObject::tr("&Restore"), rootObject);
    rootObject->connect(restoreAction, SIGNAL(triggered()), rootObject, SLOT(showNormal()));
    QAction *quitAction = new QAction(QObject::tr("&Quit"), rootObject);
    rootObject->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *trayIconMenu = new QMenu();
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    TrayIcon *trayIcon = new TrayIcon(rootObject);
    // We first foward the activated signal back into the trayIcon, if it was a left click this will emit a triggered signal
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), trayIcon, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    QObject::connect(trayIcon, SIGNAL(triggered()), rootObject, SLOT(trayIconTriggered()));

    trayIcon->setObjectName("TrayIcon");
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/trayicon.svg"));
    trayIcon->setToolTip("My icon tooltip");
    trayIcon->show();

    return app.exec();
}
