#include "simulation.h"
#include "timewheel.h"
#include "db/netlist.h"
#include "db/net.h"
#include "event.h"

#include <QVector>
#include <QDebug>

Simulation::Simulation(std::shared_ptr<Netlist> netlist)
    : mTimeWheel{}
    , mNetlist(netlist)
{
}

void Simulation::eventDrivenSimulation(QMap<QString, size_t> primaryInputs) {
    auto primaryInputNets = mNetlist->getPrimaryInputNets();

    for(auto input = primaryInputs.begin(); input != primaryInputs.end(); ++input) {
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
            initialEvents.push_back(std::make_shared<Event>(startTime, gate));
        }
    }

    mTimeWheel.insert(initialEvents);

    size_t currentTime = startTime;

    for(; currentTime < mTimeWheel.length(); ++ currentTime) {
        auto currentEvents = mTimeWheel[currentTime];
        auto futureEvents = QVector<std::shared_ptr<Event>>{};
        for(auto event : currentEvents) {
            auto currentGate = event->getGate();
            auto oldValue = currentGate->getValue();
            auto newValue = currentGate->simulate();

            if(oldValue != newValue) {
                qDebug() << "time: " << currentTime
                                  << "; gate: " << currentGate->getName()
                                  << "; old value: " << static_cast<int>(oldValue)
                                  << "; new value: " << static_cast<int>(newValue);

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
}





























