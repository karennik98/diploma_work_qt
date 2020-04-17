#ifndef GATE_H
#define GATE_H

#include <QString>
#include <QVector>

#include <memory>

class Net;

enum class GateType {
    AND,
    OR,
    NOT,
    XOR
};

class Gate
{
public:
    Gate();
    virtual size_t simulate() = 0;
    void setName(const QString& name);
    QString getName() const;
    void setDelay(const size_t delay);
    size_t getDelay() const;
    void setType(GateType type) const;
    GateType getType() const;

private:
    QString mName;
    size_t mDelay;
    size_t mValue;
    QVector<std::shared_ptr<Net>> mInputNets;
    std::shared_ptr<Net> mOutNet;
    GateType mType;
};

#endif // GATE_H
