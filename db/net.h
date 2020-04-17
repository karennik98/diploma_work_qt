#ifndef NET_H
#define NET_H

#include <QString>
#include <QVector>

class Gate;

class Net
{
public:
    Net();
private:
    QString mName;
    QVector<Gate> mGates;
    size_t mValue;
    size_t mOldValue;
};

#endif // NET_H
