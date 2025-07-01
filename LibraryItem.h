#pragma once

#include <QString>
#include <QUuid>

class Library;

class LibraryItem {
    QString name;
    Library *lib;
    QUuid id;

public:
    LibraryItem(const QString &name, Library *lib = nullptr,
                const QUuid &id = QUuid::createUuid());
    virtual ~LibraryItem() = 0;

    void setName(const QString &name);
    QString getName() const;

    Library *getLibrary() const;
    QUuid getId() const;
};
