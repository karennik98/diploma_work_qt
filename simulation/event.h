#ifndef EVENT_H
#define EVENT_H

#include "db/gate.h"

#include <memory>

class Event
{
public:
    Event() = default;
    Event(size_t time, std::shared_ptr<Gate> gate)
        : mTime(time)
        , mGate(gate)
    {}
    Event(size_t newValue, size_t time, std::shared_ptr<Gate> gate)
        : mNewValue(newValue)
        , mTime(time)
        , mGate(gate)
    {}
public:
    std::shared_ptr<Gate> getGate() const { return mGate;     }
    size_t getTime() const                { return mTime;     }
    size_t getNewValue() const            { return mNewValue; }
public:
    size_t mNewValue;
    size_t mTime;
    std::shared_ptr<Gate> mGate;
};

#endif // EVENT_H
