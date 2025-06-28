#pragma once

#include <QString>
#include <QList>

class Composition;
class Library;

class Playlist {
    QString title;
    QList<Composition *> compositions;
    Library *lib;

public:
    Playlist(const QString &title = "", Library *lib = nullptr);
    ~Playlist();

    void setTitle(const QString &title);
    QString getTitle() const;

    void addComposition(Composition *composition);
    const QList<Composition *> &getCompositions() const;

    int size() const;
    bool isEmpty() const;
};
