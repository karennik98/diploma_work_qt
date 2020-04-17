#ifndef NETLISTBUILDER_H
#define NETLISTBUILDER_H

#include <QString>

#include <memory>

class Netlist;

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
    void removeComment(QString& line) const;
    bool addGate(QString& line);
    bool addNet(QString& line);
private:
    QString mFilePath;
    std::shared_ptr<Netlist> mNetlist;
};

#endif // NETLISTBUILDER_H
