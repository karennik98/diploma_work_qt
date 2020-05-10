#include <QApplication>
#include <QDebug>

#include "gui/mainwindow.h"

#include "netlist_builder/netlistbuilder.h"
#include "db/netlist.h"
#include "simulation/simulation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    NetlistBuilder builder(":/verilog_files/input_verilog.v");
    builder.buildNetlist();
    auto netlist = builder.getNetlist();

    Simulation simulation(netlist);

    auto inputNets = netlist->getPrimaryInputNets();
    QMap<QString, size_t> primaryInputs {};
    std::srand(static_cast<unsigned int>(time(nullptr)));
    for(int i = 0; i < 5; ++i) {
        // generate random primary inputs
        srand(static_cast<unsigned int>(time(nullptr)));
        size_t randomLogicValue;
        for(const auto& el: inputNets) {
            randomLogicValue = rand() % 2;
            primaryInputs.insert(el->getName(), randomLogicValue);
        }
        qDebug()<<primaryInputs;
        primaryInputs.clear();
        simulation.eventDrivenSimulation(primaryInputs);
        qDebug()<<"______________________________________________________________________";
        qDebug()<<"";
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
