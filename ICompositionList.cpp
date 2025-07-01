#include "ICompositionList.h"
#include "Composition.h"

ICompositionList::ICompositionList(const QString &name) :
    Identifiable{name} {}

ICompositionList::~ICompositionList() {}

void ICompositionList::addComposition(Composition *composition) {
    Q_ASSERT(composition);
    compositions.append(composition);
}

bool ICompositionList::removeComposition(Composition *composition) {
    Q_ASSERT(composition);
    return compositions.removeOne(composition);
}

bool ICompositionList::containsComposition(Composition *composition) const {
    Q_ASSERT(composition);
    for (auto c : std::as_const(compositions)) {
        if (*c == *composition) {
            return true;
        }
    }
    return false;
}

const QList<Composition *> &ICompositionList::getCompositions() const {
    return compositions;
}

int ICompositionList::size() const {
    return compositions.size();
}

bool ICompositionList::isEmpty() const {
    return (size() == 0);
}
