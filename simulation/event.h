#ifndef EVENT_H
#define EVENT_H

#include "db/gate.h"

#include <memory>

class Event
{
public:
    Event() = default;
    Event(size_t newValue, size_t time, std::shared_ptr<Gate> gate);
public:
    std::shared_ptr<Gate> getGate() const;
public:
    size_t mNewValue;
    size_t mTime;
    std::shared_ptr<Gate> mGate;
};

#endif // EVENT_H
