#include "net.h"


Net::Net(NetType type, const QString &name) {
    setType(type);
    setName(name);
    setGates({});
//    setValue({});
}

Net::Net(NetType type, const QString &name, QVector<std::shared_ptr<Gate>> gates) : Net(type, name) {
    setGates(gates);
}

void Net::setValue(size_t value) {
    if(value <=1 ) {
        mOldValue = mValue;
        mValue = value;
    } else {
        throw  std::runtime_error("Wrong net value!");
    }
}
