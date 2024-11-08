#ifndef COMMANDUTIL_H
#define COMMANDUTIL_H

#include <QException>
#include <QString>
#include <QStringList>

namespace util::cmd
{

struct ExecutionError : public QException {};

QString exec(const QString &cmd,QStringList args = {});

}

#endif // COMMANDUTIL_H
