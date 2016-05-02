#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QApplication>
#include <QSystemTrayIcon>

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = 0);

public slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    QObject *m_parent;
};

#endif // TRAYICON_H
