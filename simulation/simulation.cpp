#include "simulation.h"
#include "timewheel.h"
#include "db/netlist.h"
#include "db/net.h"
#include "event.h"
#include "netlist_builder/verilogkeywords.h"

#include <QVector>
#include <QDebug>

Simulation::Simulation(std::shared_ptr<Netlist> netlist)
    : mNetlist(netlist)
    , mOutput(std::make_shared<QStringList>())
{
}

void Simulation::eventDrivenSimulation(QVector<QMap<QString, size_t>> primaryInputs) {
    setupDumpedNets();

    auto primaryInputNets = mNetlist->getPrimaryInputNets();
    TimeWheel mTimeWheel;
    size_t currentTime;
    for(int i=0; i < primaryInputs.size(); ++i) {

        QString inputVectror {};
        for(auto input = primaryInputs[i].begin(); input != primaryInputs[i].end(); ++input) {
            inputVectror += input.key() + " : " + QString::number(input.value()) + "\n";
        }
        mOutput->push_back("Input vector");
        mOutput->push_back(inputVectror);
        mOutput->push_back("Events list:");

        for(auto input = primaryInputs[i].begin(); input != primaryInputs[i].end(); ++input) {
            auto net = primaryInputNets.find(input.key());
            if(net != primaryInputNets.end()) {
                net.value()->setValue(input.value());
            }
        }

        QVector<std::shared_ptr<Event>> initialEvents;
        const size_t startTime = 0;
        for(auto net : primaryInputNets) {
            auto gates = net->getGates();
            for(auto gate : gates) {
                if(!isOnEventList(initialEvents, gate)) {
                    initialEvents.push_back(std::make_shared<Event>(startTime, gate));
                }
            }
        }

        mTimeWheel.insert(initialEvents);

        currentTime = startTime;

        for(; currentTime < mTimeWheel.length(); ++ currentTime) {
            auto currentEvents = mTimeWheel[currentTime];
            auto futureEvents = QVector<std::shared_ptr<Event>>{};
            for(auto event : currentEvents) {
                auto currentGate = event->getGate();
                auto oldValue = currentGate->getValue();
                auto newValue = currentGate->simulate();

                if(oldValue != newValue) {
                    mOutput->push_back("time: " + QString::number(currentTime) +
                                     " gate: " + currentGate->getName() + "<" + VerilogKeywords::getGateTypeStr(currentGate->getType()) + "> "
                                     " old value: " + QString::number(static_cast<int>(oldValue)) +
                                     " new value: " + QString::number(static_cast<int>(newValue)));

                    auto gateOutputNet = currentGate->getOutputNet();
                    if(gateOutputNet) {
                        auto gates = gateOutputNet->getGates();
                        for(auto gate: gates) {
                            futureEvents.push_back(std::make_shared<Event>(
                                                       currentTime + currentGate->getDelay(),
                                                       gate));
                        }
                    }
                }
                mTimeWheel.insert(futureEvents);
            }
        }
        mOutput->push_back("______________________________________________________________________\n");
    }
}


bool Simulation::isOnEventList(QVector<std::shared_ptr<Event>>& events, std::shared_ptr<Gate> gate) const {
    for(const auto& event : events) {
        if(*event->getGate() == *gate) {
            return true;
        }
    }
    return false;
}

void Simulation::setupDumpedNets() {
    auto primaryInputNets = mNetlist->getPrimaryInputNets();
    for(auto net : primaryInputNets) {
        mDumpedData.insert(net->getName(), std::make_shared<QLineSeries>());
    }

    auto primaryOutputs = mNetlist->getPrimaryOutputNets();
    for(auto net : primaryOutputs) {
        mDumpedData.insert(net->getName(), std::make_shared<QLineSeries>());
    }
}






























