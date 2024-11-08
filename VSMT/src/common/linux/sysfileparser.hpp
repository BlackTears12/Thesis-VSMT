#ifndef SYSFILEPARSER_HPP
#define SYSFILEPARSER_HPP

#include <QFile>
#include <QMap>
#include <QString>
#include <optional>
#include <qdebug.h>

namespace util
{

using std::optional;

class FileNotFoundException : public std::exception
{
public:
    FileNotFoundException(QString filename) : file(filename) {}
    QString fileName() const { return file; }
private:
    QString file;
};

class SysFileParser
{
public:
    SysFileParser(QString fileName);
    optional<const QStringList> valueAt(QString key);
private:
    void parseLine(const QString &line);
    QMap<QString,QStringList> values;
    QFile file;
};

}

#endif // SYSFILEPARSER_HPP
