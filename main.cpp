#include <QApplication>
#include <QDebug>

#include "gui/mainwindow.h"

#include "netlist_builder/netlistbuilder.h"
#include "db/netlist.h"
#include "simulation/simulation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

//    NetlistBuilder builder(":/verilog_files/input_verilog.v");
//    builder.buildNetlist();
//    auto netlist = builder.getNetlist();

//    Simulation simulation(netlist);

//    srand(static_cast<unsigned int>(time(nullptr)));

//    auto inputNets = netlist->getPrimaryInputNets();
//    QVector<QMap<QString, size_t>> primaryInputs {};
//    primaryInputs.resize(5);
//    for(int i = 0; i < 5; ++i) {
//        // generate random primary inputs
//        for(const auto& el: inputNets) {
//            primaryInputs[i].insert(el->getName(), rand() % 2);
//        }
//    }
//    qDebug()<<primaryInputs<<'\n';
//    simulation.eventDrivenSimulation(primaryInputs);

    mainWindow.show();

    return app.exec();
}
