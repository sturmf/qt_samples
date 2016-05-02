#ifndef TRAYICON_H
#define TRAYICON_H
#include <iostream>
#include <QObject>
#include <QSystemTrayIcon>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = 0) : QSystemTrayIcon(parent){}

signals:
    void triggered();

public slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason) {
        std::cout << "activated" << std::endl;
        if (reason == QSystemTrayIcon::Trigger) {
            std::cout << "tiggered" << std::endl;
            emit triggered();
        }
    }
};

#endif // TRAYICON_H
