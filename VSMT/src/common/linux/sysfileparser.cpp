#include "sysfileparser.hpp"

namespace util
{

SysFileParser::SysFileParser(QString fileName): file(fileName)
{
    if(!file.open(QIODevice::ReadOnly)) {
        throw FileNotFoundException(fileName);
    }

    QByteArray line = file.readLine();
    while(!line.isEmpty()) {
        parseLine(QString{line}.trimmed());
        line = file.readLine();
    }
}

optional<const QStringList> SysFileParser::valueAt(QString key)
{
    if(values.contains(key))
        return values[key];
    return {};
}

void SysFileParser::parseLine(const QString &line)
{
    auto parts = line.trimmed().split(':');
    if(parts.size() < 2)
        return;

    auto vals = parts[1].split(' ');
    vals.removeAll(QString(""));

    for(auto& e : vals){
        e = e.trimmed();
    }
    auto key = parts[0].trimmed();

    values.insert(key,QStringList{vals});
}

}
