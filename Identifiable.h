#pragma once

#include <QString>
#include <QUuid>

class Identifiable {
    QString name;
    QUuid id;

    void setId(const QUuid &id);

protected:
    Identifiable(const QString &name, const QUuid &id = QUuid::createUuid());

public:
    virtual ~Identifiable() = 0;

    void setName(const QString &name);
    const QString &getName() const;

    const QUuid &getId() const;

    friend class AppData;
};
