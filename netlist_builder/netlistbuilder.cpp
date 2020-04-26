#include "netlistbuilder.h"
#include "verilogkeywords.h"
#include "db/net.h"
#include "db/netlist.h"

#include <QTextStream>
#include <QException>
#include <QDebug>

NetlistBuilder::NetlistBuilder(const QString &path)
    : mFilePath(path)
    , mFile(nullptr)
    , mNetlist{}
{
}

bool NetlistBuilder::buildNetlist() {
    mFile = std::make_shared<QFile>();
    mFile->setFileName(mFilePath);
    mFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fileStream(&*mFile);

    mLine =  mLine = fileStream.readLine();
    while(!mLine.isNull()) {
        removeComment();
        removeWhitespaces();

        if(mLine.isEmpty()) {
            continue;
        }

        buildFromLine();

        mLine = fileStream.readLine();
    }

    return true;
}

void NetlistBuilder::buildFromLine() {
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
    } else if(VerilogKeywords::isGate(keyword)) {
        GateType type = VerilogKeywords::getGateType(keyword);

        mLine.remove(keyword);
        removeWhitespaces();

        QString gateName = getGateName();

        mLine.remove(gateName);
        removeWhitespaces();

        QVector<std::shared_ptr<Net>> nets = getGateNets();
        if(nets.size() > 1) {
            if(type == GateType::NOT) {
                std::shared_ptr<Gate> gate{new Gate{ type, gateName, nets[0], {nets[1]}}};
            }
            std::shared_ptr<Gate> gate{new Gate{ type, gateName, nets[0], {nets[1], nets[2]}}};
            addGate(gate);
        }
    } else if(VerilogKeywords::isStartModule(keyword)) {
        // TODO
    } else if(VerilogKeywords::isEndModule(keyword)) {
        //TODO
    } else {
        throw std::runtime_error("Invalid verilog keyword");
    }
}

void NetlistBuilder::addNet(const QString& name, NetType type) {
    try {
        std::shared_ptr<Net> net = std::make_shared<Net>(type, name);
        mNetlist->setNet(net);
    } catch (...) {
        qDebug()<<"haaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    }
}

void NetlistBuilder::addGate(const std::shared_ptr<Gate> &gate) {
    mNetlist->setGate(gate);
}

QStringList NetlistBuilder::getNetNames() /*const*/ {
    QStringList names;
    std::string line = mLine.toStdString();

    if(mLine.contains(",")) {
        std::string delimater = ",";
        size_t pos = 0;
        std::string name;
        while ((pos = line.find(delimater)) != std::string::npos)
        {
            name = line.substr(0, pos);
            removeWhitespaces(name);
            names.push_back(QString::fromStdString(name));
            line.erase(0, pos + delimater.length());
        }

    }

    size_t endPos = line.find(";");
    names.push_back(QString::fromStdString(line.substr(0, endPos)));

    mLine = QString::fromStdString(line);

    return names;
}

QString NetlistBuilder::getGateName() const {
    return QString::fromStdString(mLine.toStdString().substr(0, mLine.toStdString().find("(")));
}

QVector<std::shared_ptr<Net>> NetlistBuilder::getGateNets() const {
    QVector<std::shared_ptr<Net>> nets{};

    if(mLine.contains(",")) {
        std::string delimater = ",";
        size_t pos = 0;
        std::string name;

        while ((pos = mLine.toStdString().find(delimater)) != std::string::npos)
        {
            name = mLine.toStdString().substr(0, pos);
            removeWhitespaces(name);
            std::shared_ptr<Net> net = mNetlist->getNetByName(QString::fromStdString(name));
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
        std::shared_ptr<Net> net = mNetlist->getNetByName(name);
        if(net) {
            nets.push_back(net);
        } else {
            throw std::runtime_error("unknown net name");
        }
    }
    return nets;
}

void NetlistBuilder::removeComment() {
    std::string line =  mLine.toStdString();
    if(size_t pos = line.find("//"); pos != std::string::npos) {
        line.replace(pos, line.size()-1, "");
    }
    mLine = QString::fromStdString(line);
}

void NetlistBuilder::removeWhitespaces() {
    std::string line = mLine.toStdString();
    for(auto& el : line)
    {
        if(el == ' ')
        {
            line.erase(line.find(" "), 1);
        }
    }
    mLine = QString::fromStdString(line);
}

void NetlistBuilder::removeWhitespaces(std::string &str) const {
    for(auto& el : str)
    {
        if(el == ' ')
        {
            str.erase(str.find(" "), 1);
        }
    }
}














