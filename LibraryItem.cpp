#include "LibraryItem.h"

#include <QUuid>

LibraryItem::LibraryItem(const QString &name, Library *lib) :
    id{QUuid::createUuid().toString(QUuid::WithoutBraces)},
    name{name}, lib{lib} {}

LibraryItem::~LibraryItem() {}

Library *LibraryItem::getLibrary() const {
    return lib;
}

QString LibraryItem::getId() const {
    return id;
}

void LibraryItem::setName(const QString &name) {
    this->name = name;
}

QString LibraryItem::getName() const {
    return name;
}
