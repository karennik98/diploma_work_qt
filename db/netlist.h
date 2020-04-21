#ifndef NETLIST_H
#define NETLIST_H

#include <QMap>
#include <memory>

class Net;
class Gate;

class Netlist
{
public:
    Netlist() = default;
public:
    bool addGate(const std::shared_ptr<Gate>& gate);
    bool addNet(const std::shared_ptr<Net>& net);
public:
    Gate getGateByName(const QString& name) const;
    Net getNetByName(const QString& name) const;
public:
    QMap<QString, std::shared_ptr<Net>> getPrimaryInputNets() const;
    QMap<QString, std::shared_ptr<Net>> getPrimaryOutputNets() const;
private:
    QMap<QString, std::shared_ptr<Gate>> mGates;
    QMap<QString, std::shared_ptr<Net>> mNets;
};

#endif // NETLIST_H
