#ifndef APPLICATON_H
#define APPLICATON_H

#include <QObject>

class Applicaton : public QObject
{
    Q_OBJECT
public:
    explicit Applicaton(QObject *parent = nullptr);
    void exec();
signals:
};

#endif // APPLICATON_H
