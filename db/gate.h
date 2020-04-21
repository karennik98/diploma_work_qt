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
    NAND,
    XOR,
    NOR,
    XNOR,
    INVALID
};

class Gate
{
public:
    Gate(GateType type, QString name,
         std::shared_ptr<Net> outNet,
         QVector<std::shared_ptr<Net>> inputNets);// s/tex not i depqu ches karum chisht sarqes petqa jarangman shxta sarqel
public:
    size_t simulate();
public:
    void setName(const QString& name);
    void setDelay(const size_t delay);
    void setType(GateType type);
    void setValue(size_t value);
public:
    QString getName() const;
    size_t getDelay() const;
    GateType getType() const;
    size_t getValue() const;
    std::shared_ptr<Net> getOutputNet() const;
    QVector<std::shared_ptr<Net>> getInputNets();
private:
    GateType mType;
    QString mName;
    std::shared_ptr<Net> mOutputNet;
    QVector<std::shared_ptr<Net>> mInputNets;
    size_t mDelay;
    size_t mValue;
};

#endif // GATE_H
