#pragma once

#include "Identifiable.h"
#include <QList>

class Composition;

class ICompositionList : public Identifiable {
    QList<Composition *> compositions;

public:
    ICompositionList(const QString &name = "");
    virtual ~ICompositionList() = 0;

    virtual void addComposition(Composition *composition);
    virtual bool removeComposition(Composition *composition);
    bool containsComposition(Composition *composition) const;
    const QList<Composition *> &getCompositions() const;

    int size() const;
    bool isEmpty() const;
    Composition *operator[](qsizetype i);
};
