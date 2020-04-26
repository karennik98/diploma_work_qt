#include "timewheel.h"

void TimeWheel::insert(QVector<std::shared_ptr<Event>> items) {
    auto time = items[0]->getTime();
    extendCapacity(time);
    std::for_each(std::begin(items), std::end(items), [&, this](auto item) { insert(item); });
}

void TimeWheel::insert(std::shared_ptr<Event> item) {
    auto time = item->getTime();
    extendCapacity(time);
    mEvents[time].push_back(item);
}

QVector<std::shared_ptr<Event>>& TimeWheel::operator[](size_t idx) {
    return mEvents[idx];
}

void TimeWheel::extendCapacity(size_t size) {
    if(size > mEvents.capacity()) {
        mEvents.reserve(size + 1);
    }
}
