#ifndef SIMULATION_H
#define SIMULATION_H

#include <QVector>
#include <QMap>
#include <QString>

class TimeWhell;
class Netlist;

class Simulation
{
public:
    Simulation() = default;
    Simulation(std::shared_ptr<Netlist> netlist);
public:
    void eventDrivenSimulation(QMap<QString, size_t> primaryInputs);
public:
    void setNetlist(std::shared_ptr<Netlist> netlist);
    void setPrimaryInputs(QMap<QString, size_t> primaryInputs);
private:
    TimeWhell mTimeWheel;
    std::shared_ptr<Netlist> mNetlist;
};

#endif // SIMULATION_H
