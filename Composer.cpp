#include "Composer.h"
#include "Playlist.h"

Composer::Composer(const QString &name, Library *lib)
    : LibraryItem{name, lib} {}

bool Composer::addComposition(Composition *composition) {
    Q_ASSERT(composition);
    if (!compositions.contains(composition)) {
        compositions.append(composition);
        return true;
    }
    return false;
}

bool Composer::removeComposition(Composition *composition) {
    Q_ASSERT(composition);
    return compositions.removeOne(composition);
}

const QList<Composition *> &Composer::getCompositions() const {
    return compositions;
}

Playlist *Composer::getPlaylist() const {
    auto playlist = new Playlist;
    for (auto composition : std::as_const(compositions)) {
        playlist->addComposition(composition);
    }
    return playlist;
}
