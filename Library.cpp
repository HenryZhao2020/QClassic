#include "Library.h"
#include "Composition.h"

Library::~Library() {
    for (Composition *c : getCompositions()) {
        delete c;
    }
}

void Library::addComposition(Composition *composition) {
    Q_ASSERT(composition);
    if (!containsComposition(composition)) {
        ICompositionList::addComposition(composition);
    }
}

bool Library::removeComposition(Composition *composition) {
    Q_ASSERT(composition);
    bool returnVal{ICompositionList::removeComposition(composition)};
    delete composition;
    return returnVal;
}
