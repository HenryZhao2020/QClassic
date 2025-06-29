#include "AppData.h"

AppData::AppData() : repeat{Repeat::Off} {}

void AppData::setRepeat(Repeat repeat) {
    this->repeat = repeat;
}

Repeat AppData::getRepeat() const {
    return repeat;
}

AppData &AppData::instance() {
    static AppData data;
    return data;
}
