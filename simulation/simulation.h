#ifndef SIMULATION_H
#define SIMULATION_H

#include <QVector>
#include <QMap>
#include <QString>

#include "timewheel.h"

class Netlist;

class Simulation
{
public:
    Simulation() = default;
    Simulation(std::shared_ptr<Netlist> netlist);
public:
    void eventDrivenSimulation(QVector<QMap<QString, size_t>> primaryInputs);
public:
    void setNetlist(std::shared_ptr<Netlist> netlist) { netlist != nullptr ? mNetlist = netlist : throw std::runtime_error("Empty Netlist!"); }
public:
    bool isOnEventList(std::shared_ptr<Gate> gate) const;
    bool isOnEventList(QVector<std::shared_ptr<Event>>& events, std::shared_ptr<Gate> gate) const;
private:
    std::shared_ptr<Netlist> mNetlist;
};

#endif // SIMULATION_H
