#include "verilogkeywords.h"

const QString VerilogKeywords::_module = "module";
const QString VerilogKeywords::_input = "input";
const QString VerilogKeywords::_output = "output";
const QString VerilogKeywords::_wire = "wire";
const QString VerilogKeywords::_endmodule = "endmodule";
const QString VerilogKeywords::_or = "or";
const QString VerilogKeywords::_and = "and";
const QString VerilogKeywords::_xor = "xor";
const QString VerilogKeywords::_not = "not";

const QMap<QString, GateType> VerilogKeywords::gateTypes = {
    {_or, GateType::OR},
    {_and, GateType::AND},
    {_xor, GateType::XOR},
    {_not, GateType::NOT}
};

const QMap<QString, NetType> VerilogKeywords::netTypes = {
    {_input, NetType::INPUT},
    {_output, NetType::OUTPUT},
    {_wire, NetType::WIRE}
};


QString VerilogKeywords::getKeyword(const QString &line) {
    QVector<QString> keywords = { _input, _output, _wire, _endmodule, _module, _xor, _or, _and, _not };
    for(const auto& word : keywords) {
        if(line.contains(word)) {
            return word;
        }
    }
    return "";
}

bool VerilogKeywords::isGate(const QString &item) {
    if(!item.isEmpty()) {
        if(item == _or || item == _and || item == _xor || item == _not) {
            return true;
        }
    }
    return false;
}

bool VerilogKeywords::isNet(const QString &item)
{
    if(!item.isEmpty()) {
        if(item == _wire || item == _input || item == _output) {
            return true;
        }
    }
    return false;
}

bool VerilogKeywords::isStartModule(const QString &item) {
    if(!item.isEmpty()) {
        if(item == _module) {
            return true;
        }
    }
    return false;
}

bool VerilogKeywords::isEndModule(const QString &item) {
    if(!item.isEmpty()) {
        if(item == _endmodule) {
            return true;
        }
    }
    return false;
}

GateType VerilogKeywords::getGateType(const QString &keyword) {
    for(auto it = gateTypes.begin(); it != gateTypes.end(); ++it) {
        if(it.key() == keyword) {
            return it.value();
        }
    }
    return GateType::INVALID;
}

NetType VerilogKeywords::getNetType(const QString &keyword) {
    for(auto it = netTypes.begin(); it != netTypes.end(); ++it) {
        if(it.key() == keyword) {
            return it.value();
        }
    }
    return NetType::INVALID;
}














