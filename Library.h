#pragma once

#include <QList>

class Composition;
class Composer;

class Library {
    QList<Composition *> compositions;
    QList<Composer *> composers;

public:
    Library();
    ~Library();

    void addComposition(Composition *composition);
    void addComposer(Composer *composer);

    const QList<Composition *> &getCompositions() const;
    const QList<Composer *> &getComposers() const;
};
