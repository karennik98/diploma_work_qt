#ifndef TIMEWHEEL_H
#define TIMEWHEEL_H

#include "event.h"

#include <QVector>

class Event;

class TimeWheel
{
public:
    TimeWheel();
public:
    bool addEventList(QVector<std::shared_ptr<Event>> eventList);
public:
    size_t length() const;
public:
    QVector<std::shared_ptr<Event>>& operator[](size_t idx);
private:
    QVector<QVector<std::shared_ptr<Event>>> mEvents;
};

#endif // TIMEWHEEL_H
