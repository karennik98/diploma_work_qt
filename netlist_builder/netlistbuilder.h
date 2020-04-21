#ifndef NETLISTBUILDER_H
#define NETLISTBUILDER_H

#include "db/gate.h"
#include "db/net.h"

#include <QString>
#include <QFile>

#include <memory>

class Netlist;
class Net;
class Gate;

class NetlistBuilder
{
public:
    NetlistBuilder() = default;
    NetlistBuilder(const QString& path);
    void setFilePath(const QString& path) { mFilePath = path;}
    bool buildNetlist();
    std::shared_ptr<Netlist> getNetlist() const { return mNetlist; }
private:
    QString getLine() const;
    QStringList getNetNames() const;

    QString getGateName() const;
    QVector<Net> getGateNets() const;
private:
    void removeComment() const;
    void removeWhitespaces() const;
private:
    bool addGate(QString& line);
    bool addNet(QString& line, NetType type);
private:
    void removeWhitespaces(std::string& str) const;
private:
    QString mFilePath;
    QString mLine;
    std::shared_ptr<QFile> mFile;
    std::shared_ptr<Netlist> mNetlist;
};

#endif // NETLISTBUILDER_H
