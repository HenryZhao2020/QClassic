#include "Library.h"
#include "Composition.h"
#include "Composer.h"

Library::Library() {}

Library::~Library() {
    for (auto c : std::as_const(compositions)) delete c;
    for (auto c : std::as_const(composers)) delete c;
}

void Library::addComposition(Composition *composition) {
    compositions.append(composition);
}

void Library::addComposer(Composer *composer) {
    composers.append(composer);
}

const QList<Composition *> &Library::getCompositions() const {
    return compositions;
}

const QList<Composer *> &Library::getComposers() const {
    return composers;
}
