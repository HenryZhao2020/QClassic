#include "Library.h"
#include "Composition.h"

Library::~Library() {
    for (Composition *c : getCompositions()) {
        delete c;
    }
}

bool Library::removeComposition(Composition *composition) {
    Q_ASSERT(composition);
    bool returnVal{ICompositionList::removeComposition(composition)};
    delete composition;
    return returnVal;
}
