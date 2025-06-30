#include "Library.h"
#include "Composition.h"

Library::Library() {}

Library::~Library() {
    for (auto c : std::as_const(compositions)) {
        delete c;
    }
}

bool Library::addComposition(Composition *composition) {
    Q_ASSERT(composition);
    if (!compositions.contains(composition)) {
        compositions.append(composition);
        return true;
    }
    return false;
}

bool Library::removeComposition(Composition *composition) {
    Q_ASSERT(composition);
    return compositions.removeOne(composition);
}

const QList<Composition *> &Library::getCompositions() const {
    return compositions;
}
