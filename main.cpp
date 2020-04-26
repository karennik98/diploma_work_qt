#include <QCoreApplication>

#include "netlist_builder/netlistbuilder.h"
#include "db/netlist.h"
#include "simulation/simulation.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NetlistBuilder builder(":/verilog_files/simple.v");
    builder.buildNetlist();
    auto netlist = builder.getNetlist();

    // generate random primary inputs
    srand(static_cast<unsigned int>(time(nullptr)));
    auto inputNets = netlist->getPrimaryInputNets();
    QMap<QString, size_t> primaryInputs {};
    size_t randomLogicValue;
    for(const auto& el: inputNets) {
        randomLogicValue = rand() % 2;
        primaryInputs.insert(el->getName(), randomLogicValue);
    }

    Simulation simulation(netlist);
    simulation.eventDrivenSimulation(primaryInputs);

    return a.exec();
}
