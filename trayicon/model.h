#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QSystemTrayIcon>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);


signals:

public slots:
    void refresh();

private:
    void updateTrayIcon(QIcon &icon, const QString &title = "", const QString &msg = "");
};

#endif // MODEL_H
