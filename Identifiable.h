#pragma once

#include <QString>
#include <QUuid>

class Identifiable {
    QString name;
    QUuid id;

    void setId(const QUuid &id);

public:
    Identifiable(const QString &name, const QUuid &id = QUuid::createUuid());
    virtual ~Identifiable() = 0;

    void setName(const QString &name);
    QString getName() const;

    QUuid getId() const;

    friend class AppData;
};
