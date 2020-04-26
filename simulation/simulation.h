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
    void eventDrivenSimulation(QMap<QString, size_t> primaryInputs);
public:
    void setNetlist(std::shared_ptr<Netlist> netlist) { netlist != nullptr ? mNetlist = netlist : throw std::runtime_error("Empty Netlist!"); }
private:
    TimeWheel mTimeWheel;
    std::shared_ptr<Netlist> mNetlist;
};

#endif // SIMULATION_H
