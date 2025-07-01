#include "LibraryItem.h"

LibraryItem::LibraryItem(const QString &name, Library *lib, const QUuid &id)
    : name{name}, lib{lib}, id{id} {}

LibraryItem::~LibraryItem() {}

void LibraryItem::setName(const QString &name) {
    this->name = name;
}

QString LibraryItem::getName() const {
    return name;
}

Library *LibraryItem::getLibrary() const {
    return lib;
}

QUuid LibraryItem::getId() const {
    return id;
}
