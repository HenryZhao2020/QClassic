#include "AppData.h"
#include "Library.h"

AppData::AppData() :
    lib{new Library},
    repeat{Repeat::Off},
    sideBarVisible{true} {}

AppData::~AppData() {
    delete lib;
}

Library *AppData::getLibrary() const {
    return lib;
}

void AppData::setRepeat(Repeat repeat) {
    this->repeat = repeat;
}

Repeat AppData::getRepeat() const {
    return repeat;
}

void AppData::setSideBarVisible(bool visible) {
    sideBarVisible = visible;
}

bool AppData::isSideBarVisible() const {
    return sideBarVisible;
}

AppData &AppData::instance() {
    static AppData data;
    return data;
}
