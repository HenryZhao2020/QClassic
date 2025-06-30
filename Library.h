#pragma once

#include <QList>

class Composition;

class Library {
    QList<Composition *> compositions;

    Library();

public:
    ~Library();

    bool addComposition(Composition *composition);
    bool removeComposition(Composition *composition);
    const QList<Composition *> &getCompositions() const;

    friend class AppData;
};
