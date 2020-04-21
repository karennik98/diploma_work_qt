#ifndef VERILOGKEYWORDS_H
#define VERILOGKEYWORDS_H

#include "db/gate.h"
#include "db/net.h"

#include <QString>
#include <QMap>

class VerilogKeywords
{
public:
    static const QString _module;
    static const QString _input;
    static const QString _output;
    static const QString _wire;
    static const QString _endmodule;
    static const QString _or;
    static const QString _xor;
    static const QString _and;
    static const QString _not;
    static const QString _nand;
    static const QString _xnor;
    static const QString _nor;

    static const QMap<QString, GateType> gateTypes;
    static const QMap<QString, NetType> netTypes;

public:
    static QString getKeyword(const QString& line);
    static bool isGate(const QString& item);
    static bool isNet(const QString& item);
    static bool isStartModule(const QString& item);
    static bool isEndModule(const QString& item);

    static GateType getGateType(const QString& keyword);
    static NetType getNetType(const QString& keyword);
};

#endif // VERILOGKEYWORDS_H
