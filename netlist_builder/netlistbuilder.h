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
    bool buildNetlist();
    void setFilePath(const QString& path)       { mFilePath = path; }
    std::shared_ptr<Netlist> getNetlist() const { return mNetlist;  }
private:
    QStringList getNetNames() /*const*/;
    QString getGateName() const;
    QVector<std::shared_ptr<Net>> getGateNets();
private:
    void removeComment();
    void removeWhitespaces();
    void removeWhitespaces(std::string& str) const;
    void removeUselessSimbols();
private:
//    bool addGate(QString& line);
    void addNet(const QString& name, NetType type);
    void addGate(const std::shared_ptr<Gate>& gate);
private:
    void buildFromLine();
private:
    QString mFilePath;
    QString mLine;
    std::shared_ptr<QFile> mFile;
    std::shared_ptr<Netlist> mNetlist;
};

#endif // NETLISTBUILDER_H
