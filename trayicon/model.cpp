#include <iostream>
#include "model.h"

extern QObject *rootObject;

Model::Model(QObject *parent) : QObject(parent)
{
}


void Model::refresh()
{
    std::cout << "refresh called in model" << std::endl;


    bool isError = true;
    // Now update the trayicon according to the found changes
    if (isError) {
        updateTrayIcon(QIcon(":/trayicon_error.svg"), "Error", "Some error text");
    }
    else {
        updateTrayIcon(QIcon(":/trayicon.svg"));
    }
}


void Model::updateTrayIcon(QIcon &icon, const QString &title, const QString &msg) {
    QSystemTrayIcon *trayIcon = rootObject->findChild<QSystemTrayIcon *>("TrayIcon");

    if (trayIcon != NULL) {
        trayIcon->setIcon(icon);
        if (msg != "") {
            trayIcon->showMessage(title, msg);
        }
    }
}
