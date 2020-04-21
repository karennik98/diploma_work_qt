#include "netlistbuilder.h"
#include "verilogkeywords.h"
#include "db/net.h"
#include "db/netlist.h"

#include <QTextStream>


NetlistBuilder::NetlistBuilder(const QString &path)
    : mFilePath(path)
    , mFile(new QFile(path))
{
    mFile->open(QIODevice::ReadOnly | QIODevice::Text);
}

bool NetlistBuilder::buildNetlist() {
    QTextStream fileStream(&*mFile);
    while(!mFile->atEnd()) {
        mLine = fileStream.readLine();

        removeComment();
        removeWhitespaces();

        if(mLine.isEmpty()) {
            continue;
        }

        QString keyword = VerilogKeywords::getKeyword(mLine);

        if(VerilogKeywords::isNet(keyword)) {
            mLine.remove(keyword);
            removeWhitespaces();

            QStringList netNames = getNetNames();
            NetType type = VerilogKeywords::getNetType(keyword);

            if(netNames.size() > 0) {
                for(auto& name : netNames) {
                    addNet(name, type);
                }
            }
        }

        if(VerilogKeywords::isGate(keyword)) {
            GateType type = VerilogKeywords::getGateType(keyword);

            mLine.remove(keyword);
            removeWhitespaces();

            QString gateName = getGateName();

            mLine.remove(gateName);
            removeWhitespaces();

            QVector<Net> nets = getGateNets();
            if(nets.size() > 1) {
                std::shared_ptr<Gate> gate{new Gate{type, gateName, nets[0], {nets[1], nets[2]}};
            }

        }
    }
}

QString NetlistBuilder::getLine() const {

}

QStringList NetlistBuilder::getNetNames() const {
    QStringList names;
    if(mLine.contains(",")) {
        std::string delimater = ",";
        size_t pos = 0;
        std::string name;
        while ((pos = mLine.toStdString().find(delimater)) != std::string::npos)
        {
            name = mLine.toStdString().substr(0, pos);
            removeWhitespaces(name);
            names.push_back(QString::fromStdString(name));
            mLine.toStdString().erase(0, pos + delimater.length());
        }
    } else {
      size_t endPos = mLine.toStdString().find(";") - 1;
      names.push_back(QString::fromStdString(mLine.toStdString().substr(0, endPos)));
    }

    return names;
}

QString NetlistBuilder::getGateName() const {
    return QString::fromStdString(mLine.toStdString().substr(0, mLine.toStdString().find("(")));
}

QVector<Net> NetlistBuilder::getGateNets() const {
    QVector<Net> nets{};

    if(mLine.contains(",")) {
        std::string delimater = ",";
        size_t pos = 0;
        std::string name;

        while ((pos = mLine.toStdString().find(delimater)) != std::string::npos)
        {
            name = mLine.toStdString().substr(0, pos);
            removeWhitespaces(name);
            Net net = mNetlist->getNetByName(QString::fromStdString(name));
            if(net) {
                nets.push_back(net);
            } else {
                throw std::runtime_error("unknown net name");
            }
            mLine.toStdString().erase(0, pos + delimater.length());
        }
    } else {
        size_t end = mLine.toStdString().find(")") - 1;
        QString name = QString::fromStdString(mLine.toStdString().substr(1, end));
        Net net = mNetlist->getNetByName(name);
        if(net) {
            nets.push_back(net);
        } else {
            throw std::runtime_error("unknown net name");
        }
    }
}

void NetlistBuilder::removeComment() const {

}

void NetlistBuilder::removeWhitespaces() const {

}

bool NetlistBuilder::addGate(QString &line) {

}

bool NetlistBuilder::addNet(QString &line, NetType type) {

}












