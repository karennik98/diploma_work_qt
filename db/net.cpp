#include "net.h"


Net::Net(NetType type, const QString &name) {
    setType(type);
    setName(name);
    setGates({});
    setValue({});
}

Net::Net(NetType type, const QString &name, QVector<std::shared_ptr<Gate>> gates) : Net(type, name) {
    setGates(gates);
}
