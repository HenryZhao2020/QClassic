#include "Identifiable.h"

Identifiable::Identifiable(const QString &name, const QUuid &id) :
    name{name}, id{id} {}

Identifiable::~Identifiable() {}

void Identifiable::setName(const QString &name) {
    this->name = name;
}

const QString &Identifiable::getName() const {
    return name;
}

void Identifiable::setId(const QUuid &id) {
    this->id = id;
}

const QUuid &Identifiable::getId() const {
    return id;
}
