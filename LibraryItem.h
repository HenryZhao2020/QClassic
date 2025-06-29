#pragma once

#include <QString>

class Library;

class LibraryItem {
    QString id;
    QString name;
    Library *lib;

protected:
    Library *getLibrary() const;

public:
    LibraryItem(const QString &name, Library *lib = nullptr);
    virtual ~LibraryItem() = 0;

    QString getId() const;

    void setName(const QString &name);
    QString getName() const;
};
