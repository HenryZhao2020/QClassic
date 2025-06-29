#include "Library.h"
#include "Composition.h"
#include "Composer.h"

Library::Library() {}

Library::~Library() {
    for (auto c : std::as_const(compositions)) delete c;
    for (auto c : std::as_const(composers)) delete c;
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

bool Library::addComposer(Composer *composer) {
    Q_ASSERT(composer);
    if (!composers.contains(composer)) {
        composers.append(composer);
        return true;
    }
    return false;
}

bool Library::removeComposer(Composer *composer) {
    Q_ASSERT(composer);
    return composers.removeOne(composer);
}

const QList<Composer *> &Library::getComposers() const {
    return composers;
}
