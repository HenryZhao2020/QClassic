#pragma once

#include "LibraryItem.h"

#include <QList>
#include <QStringList>

class Composition;
class Library;
class Playlist;

class Composer : public LibraryItem {
    QList<Composition *> compositions;

public:
    Composer(const QString &name, Library *lib = nullptr);

    bool addComposition(Composition *composition);
    bool removeComposition(Composition *composition);
    const QList<Composition *> &getCompositions() const;

    Playlist *getPlaylist() const;
};
