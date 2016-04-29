#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QVariant>
#include "model.h"

// This is bad but we need the rootObject from e.g. model.cpp which otherwise has no access
QObject *rootObject = NULL;


Q_DECLARE_METATYPE(QSystemTrayIcon::ActivationReason)

int main(int argc, char *argv[])
{
    qRegisterMetaType<QSystemTrayIcon::ActivationReason>();

    QApplication app(argc, argv);

    qmlRegisterType<Model>("Model", 1,0, "Model");

    // Check if we have SysTray support
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Main"),
                                 QObject::tr("This application requires system tray support."));
        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().size() > 0)
    {
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


        QSystemTrayIcon *trayIcon = new QSystemTrayIcon(rootObject);
        //QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), rootObject, SLOT(trayIconClicked(QVariant)));
        QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), rootObject, SLOT(trayIconClicked()));

        trayIcon->setObjectName("TrayIcon");
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon(":/trayicon.svg"));
        trayIcon->setToolTip("My icon tooltip");
        trayIcon->show();
    }

    return app.exec();
}
