#include "Library.h"
#include "Composition.h"

Library::Library() {}

Library::~Library() {
    for (auto c : std::as_const(compositions)) {
        delete c;
    }
}

void Library::addComposition(Composition *composition) {
    Q_ASSERT(composition);
    compositions.append(composition);
}

void Library::removeComposition(Composition *composition) {
    Q_ASSERT(composition);
    compositions.removeOne(composition);
    delete composition;
}

bool Library::containsComposition(Composition *composition) {
    Q_ASSERT(composition);
    for (auto c : std::as_const(compositions)) {
        if (*c == *composition) {
            return true;
        }
    }
    return false;
}

const QList<Composition *> &Library::getCompositions() const {
    return compositions;
}
