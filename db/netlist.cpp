#include "netlist.h"
#include <QDebug>

bool Netlist::setGate(std::shared_ptr<Gate> gate) {
    if(gate != nullptr) {
        mGates.insert(gate->getName(), gate);
        return true;
    }
    return false;
}

bool Netlist::setNet(std::shared_ptr<Net> net) {
    if(net != nullptr) {
        mNets.insert(net->getName(), net);
        return true;
    }
    return false;
}

std::shared_ptr<Gate> Netlist::getGateByName(const QString &name) const {
    if(auto el = mGates.find(name); el != mGates.end()) {
        return *el;
    }
    return nullptr;
}

std::shared_ptr<Net> Netlist::getNetByName(const QString &name) const {
    if(auto el = mNets.find(name); el != mNets.end()) {
        return *el;
    }
    return nullptr;
}

QMap<QString, std::shared_ptr<Net> > Netlist::getPrimaryInputNets() const {
    QMap<QString, std::shared_ptr<Net>> inputNets;
    for(const auto& net : mNets) {
        if(net->getType() == NetType::INPUT) {
            inputNets.insert(net->getName(), net);
        }
    }
    return inputNets;
}

QMap<QString, std::shared_ptr<Net> > Netlist::getPrimaryOutputNets() const {
    QMap<QString, std::shared_ptr<Net>> outputNets;
    for(const auto& net : mNets) {
        if(net->getType() == NetType::OUTPUT) {
            outputNets.insert(net->getName(), net);
        }
    }
    return outputNets;
}
