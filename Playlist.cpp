#include "Playlist.h"
#include "Composition.h"

Playlist::Playlist(const QString &title, Library *lib)
    : title{title}, lib{lib} {}

Playlist::~Playlist() {
    if (!lib) {
        for (auto c : std::as_const(compositions)) delete c;
    }
}

void Playlist::setTitle(const QString &title) {
    this->title = title;
}

QString Playlist::getTitle() const {
    return title;
}

void Playlist::addComposition(Composition *composition) {
    compositions.append(composition);
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
