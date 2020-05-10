#include "timewheel.h"

void TimeWheel::insert(QVector<std::shared_ptr<Event>> items) {
    if(items.size() > 0) {
        auto time = items[0]->getTime();
        extendCapacity(time + 1);
        std::for_each(std::begin(items), std::end(items), [&, this](auto item) { insert(item); });
    }
}

void TimeWheel::insert(std::shared_ptr<Event> item) {
    auto time = item->getTime();
    extendCapacity(time);
    mEvents[time].push_back(item);
}

std::shared_ptr<Gate> TimeWheel::find(std::shared_ptr<Gate> gate) const {
    for(const auto& eventList : mEvents) {
        for(const auto& event : eventList) {
            if(*event->getGate() == *gate) {
                return std::make_shared<Gate>(*event->getGate());
            }
        }
    }
    return nullptr;
}

QVector<std::shared_ptr<Event>>& TimeWheel::operator[](size_t idx) {
    return mEvents[idx];
}

void TimeWheel::extendCapacity(size_t size) {
    if(size > mEvents.capacity()) {
        mEvents.resize(size + 1);
    }
}
