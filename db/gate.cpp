#include "gate.h"
#include "net.h"
#include "logic_operations/logicoperations.h"

Gate::Gate(GateType type, QString name, std::shared_ptr<Net> outNet, QVector<std::shared_ptr<Net> > inputNets) {
    setType(type);
    setName(name);
    mOutputNet = outNet;
    mInputNets = inputNets;
}

size_t Gate::simulate() {
    size_t output;
    switch (mType) {
        case GateType::OR: {
            output = LogicOperations::OR(mInputNets[0]->getValue(), mInputNets[1]->getValue());
            mOutputNet->setValue(output);
            setValue(output);
            return output;
        }
        case GateType::AND: {
            output = LogicOperations::AND(mInputNets[0]->getValue(), mInputNets[1]->getValue());
            mOutputNet->setValue(output);
            setValue(output);
            return output;
        }
        case GateType::NOR: {
            return 0;
        }
        case GateType::NOT: {
            output = LogicOperations::NOT(mInputNets[0]->getValue());
            mOutputNet->setValue(output);
            setValue(output);
            return output;
        }
        case GateType::XOR: {
            output = LogicOperations::XOR(mInputNets[0]->getValue(), mInputNets[1]->getValue());
            mOutputNet->setValue(output);
            setValue(output);
            return output;
        }
        case GateType::NAND: {
            output = LogicOperations::NAND(mInputNets[0]->getValue(), mInputNets[1]->getValue());
            mOutputNet->setValue(output);
            setValue(output);
            return output;
        }
        case GateType::XNOR: {
            return 0;
        }
        case GateType::INVALID: {
            throw std::runtime_error(" INVALID gate type");
        }
    }
}

bool Gate::operator==(const Gate &gate) {
    // TODO more smart
    return mName == gate.getName();
}
