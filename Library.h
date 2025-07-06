#pragma once

#include "IPieceList.h"

#include <QStringList>

class Library : public IPieceList {
    QStringList composers;

public:
    ~Library();

    void addPiece(Piece *piece) override;
    bool removePiece(Piece *piece) override;

    const QStringList &getComposers() const;
};
