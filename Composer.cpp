#include "Composer.h"
#include "Composition.h"

Composer::Composer(const QString &name) : name{name} {}

void Composer::setName(const QString &name) {
    this->name = name;
}

QString Composer::getName() const {
    return name;
}

void Composer::addComposition(Composition *composition) {
    compositions.append(composition);
}

const QList<Composition *> &Composer::getCompositions() const {
    return compositions;
}
