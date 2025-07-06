#pragma once

#include "Identifiable.h"

#include <QList>

class Piece;

class IPieceList : public Identifiable {
    QList<Piece *> pieces;

protected:
    IPieceList(const QString &name = "");

public:
    virtual ~IPieceList() = 0;

    virtual void addPiece(Piece *piece);
    virtual bool removePiece(Piece *piece);
    bool containsPiece(Piece *piece) const;
    const QList<Piece *> &getPieces() const;

    int size() const;
    bool isEmpty() const;
};
