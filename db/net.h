#ifndef NET_H
#define NET_H

#include <QString>
#include <QVector>

#include <memory>

class Gate;

enum class NetType {
    INPUT,
    WIRE,
    OUTPUT,
    INVALID
};

class Net
{
public:
    Net(NetType type, const QString& name);
    Net(NetType type, const QString& name, QVector<std::shared_ptr<Gate>> gates);
public:
    void setType(NetType type)                          { type != NetType::INVALID ? mType = type : throw  std::runtime_error("Invalid net type!"); }
    void setValue(size_t value);
    void setName(const QString& name)                   { name != "" ? mName = name : throw  std::runtime_error("Empty name value!");               }
    void setGates(QVector<std::shared_ptr<Gate>> gates) { mGates = std::move(gates); }
    void setGate(std::shared_ptr<Gate> gate)            { mGates.push_back(gate); }
public:
    size_t getValue() const                         { return mValue;    } // TODO some checks
    size_t getOldValue() const                      { return mOldValue; }
    QString getName() const                         { return mName;     }
    QVector<std::shared_ptr<Gate>> getGates() const { return mGates;    }
    NetType getType() const                         { return mType;     }
public:
    operator bool() const { return !mName.isEmpty(); }
private:
    NetType mType;
    QString mName;
    QVector<std::shared_ptr<Gate>> mGates;
    size_t mValue = 2;
    size_t mOldValue;
};

#endif // NET_H
