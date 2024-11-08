#ifndef SOCKMANAGER_H
#define SOCKMANAGER_H

#include <QObject>

class SockManager : public QObject
{
    Q_OBJECT
public:
    explicit SockManager(QObject *parent = nullptr);

signals:
};

#endif // SOCKMANAGER_H
