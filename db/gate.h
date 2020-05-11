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
    void setName(const QString& name) { name != "" ? mName = name : throw std::runtime_error("Empty gate name!");                  }
    void setDelay(const size_t delay) { mDelay = delay;                                                                            }
    void setType(GateType type)       { type != GateType::INVALID ? mType = type : throw std::runtime_error("Invalid gate type!"); }
    void setValue(size_t value)       { value <= 1 ? mValue = value : throw std::runtime_error("Wrong value!");                    }
public:
    QString getName() const                            { return mName;      } // TODO need some checks
    size_t getDelay() const                            { return mDelay;     }
    GateType getType() const                           { return mType;      }
    size_t getValue() const                            { return mValue;     }
    std::shared_ptr<Net> getOutputNet() const          { return mOutputNet; }
    QVector<std::shared_ptr<Net>> getInputNets() const { return mInputNets; }
public:
    bool operator==(const Gate& gate);
private:
    GateType mType;
    QString mName;
    std::shared_ptr<Net> mOutputNet;
    QVector<std::shared_ptr<Net>> mInputNets;
    size_t mDelay = 1;
    size_t mValue = -1;
};

#endif // GATE_H
