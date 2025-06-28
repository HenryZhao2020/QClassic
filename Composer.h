#pragma once

#include <QString>
#include <QList>

class Composition;

class Composer {
    QString name;
    QList<Composition *> compositions;

public:
    Composer(const QString &name);

    void setName(const QString &name);
    QString getName() const;

    void addComposition(Composition *composition);
    const QList<Composition *> &getCompositions() const;
};
