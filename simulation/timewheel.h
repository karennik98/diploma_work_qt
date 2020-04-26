#ifndef TIMEWHEEL_H
#define TIMEWHEEL_H

#include "event.h"

#include <QVector>

class Event;

class TimeWheel
{
public:
    TimeWheel() = default;
public:
    void insert(QVector<std::shared_ptr<Event>> items);
    void insert(std::shared_ptr<Event> item);
public:
    size_t length() const { return mEvents.size(); }
public:
    QVector<std::shared_ptr<Event>>& operator[](size_t idx);
private:
    void extendCapacity(size_t size);
private:
    QVector<QVector<std::shared_ptr<Event>>> mEvents;
};

#endif // TIMEWHEEL_H
