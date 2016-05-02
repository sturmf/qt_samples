#include <iostream>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QWindow>
#include "trayicon.h"

TrayIcon::TrayIcon(QObject *parent) : QObject(parent)
  , m_parent(parent)
{
    /*
    // Check if we have SysTray support
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Main"),
                                 QObject::tr("This application requires system tray support."));
        return 1;
    }
    */

    std::cout << "TrayIcon created" << std::endl;

    QAction *minimizeAction = new QAction(QObject::tr("Mi&nimize"), parent);
    parent->connect(minimizeAction, SIGNAL(triggered()), parent, SLOT(hide()));
    QAction *restoreAction = new QAction(QObject::tr("&Restore"), parent);
    parent->connect(restoreAction, SIGNAL(triggered()), parent, SLOT(showNormal()));
    QAction *quitAction = new QAction(QObject::tr("&Quit"), parent);
    parent->connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *trayIconMenu = new QMenu();
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(parent);
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    trayIcon->setObjectName("TrayIcon");
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/trayicon.svg"));
    trayIcon->setToolTip("My icon tooltip");
    trayIcon->show();
}


void TrayIcon::trayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        std::cout << "activated" << reason << std::endl;
        m_parent->dumpObjectInfo();
        //QWindow * window = q_m_parent
                /*
                if (!visible) {
                    showNormal()
                    raise()
                } else {
                    hide()
                }
                        */
    }
}

