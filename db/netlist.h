#ifndef NETLIST_H
#define NETLIST_H

#include <QMap>
#include <memory>

class Net;
class Gate;

class Netlist
{
public:
    Netlist();
    bool addGate(const std::shared_ptr<Gate>& gate);
    bool addNet(const std::shared_ptr<Net>& net);
private:
    QMap<QString, std::shared_ptr<Gate>> mGates;
    QMap<QString, std::shared_ptr<Net>> mNets;
};

#endif // NETLIST_H
