#ifndef NET_H
#define NET_H

#include <QString>
#include <QVector>

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
    Net(NetType type, const QString& name, QVector<std::shared_ptr<Net>> gates);
public:
    void setValue(size_t value);
    void setName(const QString& name);
    void setGate(std::shared_ptr<Gate> gate);
    void setGates(QVector<std::shared_ptr<Gate>> gates);
public:
    size_t getValue() const;
    size_t getOldValue() const;
    QString getName() const;
    QVector<std::shared_ptr<Gate>> getGates() const;
public:
    operator bool() const { return !mName.isEmpty(); }
private:
    NetType mType;
    QString mName;
    QVector<std::shared_ptr<Gate>> mGates;
    size_t mValue;
    size_t mOldValue;
};

#endif // NET_H
