#include "Library.h"

#include "Piece.h"

Library::~Library() {
    for (auto &piece : getPieces()) {
        delete piece;
    }
}

void Library::addPiece(Piece *piece) {
    Q_ASSERT(piece);
    IPieceList::addPiece(piece);

    const QString composer{piece->getComposer()};
    if (!composers.contains(composer)) {
        composers.append(composer);
    }
}

bool Library::removePiece(Piece *piece) {
    Q_ASSERT(piece);
    const bool returnVal{IPieceList::removePiece(piece)};
    delete piece;
    return returnVal;
}

const QStringList &Library::getComposers() const {
    return composers;
}
