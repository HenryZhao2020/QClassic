#pragma once

#include "LibraryItem.h"

#include <QList>
#include <QString>

class Composition;
class Library;

class Playlist : public LibraryItem {
    QList<Composition *> compositions;

public:
    Playlist(const QString &name = "", Library *lib = nullptr);
    ~Playlist();

    void addComposition(Composition *composition);
    bool removeComposition(Composition *composition);
    const QList<Composition *> &getCompositions() const;

    int size() const;
    bool isEmpty() const;
};
