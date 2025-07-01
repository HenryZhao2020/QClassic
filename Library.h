#pragma once

#include <QList>

class Composition;

class Library {
    QList<Composition *> compositions;

public:
    Library();
    ~Library();

    void addComposition(Composition *composition);
    void removeComposition(Composition *composition);
    bool containsComposition(Composition *composition);
    const QList<Composition *> &getCompositions() const;
};
