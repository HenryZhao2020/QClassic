#pragma once

#include <QList>

class Composition;
class Composer;

class Library {
    QList<Composition *> compositions;
    QList<Composer *> composers;

    bool addComposer(Composer *composer);
    bool removeComposer(Composer *composer);

public:
    Library();
    ~Library();

    bool addComposition(Composition *composition);
    bool removeComposition(Composition *composition);
    const QList<Composition *> &getCompositions() const;

    const QList<Composer *> &getComposers() const;
};
