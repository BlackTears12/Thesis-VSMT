#include "commandutil.hpp"

#include <QProcess>
#include <QTextStream>

namespace util::cmd
{

QString exec(const QString &cmd, QStringList args)
{
    QProcess process;
    process.start(cmd,args);
    process.waitForFinished();

    QTextStream stdOut(process.readAllStandardOutput());

    process.kill();
    process.close();

    if(process.error() != QProcess::UnknownError) {
        throw ExecutionError();
    }

    return stdOut.readAll().trimmed();
}

}
