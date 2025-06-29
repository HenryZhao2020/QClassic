#include "Playlist.h"
#include "Composition.h"

Playlist::Playlist(const QString &name, Library *lib)
    : LibraryItem{name, lib} {}

Playlist::~Playlist() {
    if (!getLibrary()) {
        for (auto c : std::as_const(compositions)) delete c;
    }
}

void Playlist::addComposition(Composition *composition) {
    Q_ASSERT(composition);
    compositions.append(composition);
}

bool Playlist::removeComposition(Composition *composition) {
    Q_ASSERT(composition);
    return compositions.removeOne(composition);
}

const QList<Composition *> &Playlist::getCompositions() const {
    return compositions;
}

int Playlist::size() const {
    return compositions.size();
}

bool Playlist::isEmpty() const {
    return (size() == 0);
}
