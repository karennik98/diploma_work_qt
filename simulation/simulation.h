#ifndef SIMULATION_H
#define SIMULATION_H

#include "timewheel.h"

#include <QVector>
#include <QMap>
#include <QString>
#include <QtCharts>

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
    std::shared_ptr<QStringList> getOutput() const    { return mOutput; }
public:
    QMap<QString, std::shared_ptr<QLineSeries>> getDumpedData() const  { return mDumpedData; }
public:
    bool isOnEventList(std::shared_ptr<Gate> gate) const;
    bool isOnEventList(QVector<std::shared_ptr<Event>>& events, std::shared_ptr<Gate> gate) const;
public:
    void setupDumpedNets();
private:
    std::shared_ptr<Netlist> mNetlist;
    QMap<QString, std::shared_ptr<QLineSeries>> mDumpedData;
    std::shared_ptr<QStringList> mOutput;
};

#endif // SIMULATION_H
