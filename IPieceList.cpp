#include "IPieceList.h"

#include "Piece.h"

IPieceList::IPieceList(const QString &name) : Identifiable{name} {}

IPieceList::~IPieceList() {}

void IPieceList::addPiece(Piece *piece) {
    Q_ASSERT(piece);
    pieces.append(piece);
}

bool IPieceList::removePiece(Piece *piece) {
    Q_ASSERT(piece);
    return pieces.removeOne(piece);
}

bool IPieceList::containsPiece(Piece *piece) const {
    Q_ASSERT(piece);
    for (const auto &c : getPieces()) {
        if (*c == *piece) return true;
    }
    return false;
}

const QList<Piece *> &IPieceList::getPieces() const {
    return pieces;
}

int IPieceList::size() const {
    return pieces.size();
}

bool IPieceList::isEmpty() const {
    return pieces.isEmpty();
}
