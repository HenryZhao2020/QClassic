#include "PieceMenu.h"

#include "IPieceView.h"
#include "PieceEditor.h"

PieceMenu::PieceMenu(IPieceView *pieceView) :
    QMenu{pieceView},
    pieceView{pieceView},
    playAction{new QAction{tr("Play"), this}},
    deleteAction{new QAction{tr("Remove"), this}} {

    addAction(playAction);
    addAction(deleteAction);
}

bool PieceMenu::apply(QAction *action, const QModelIndex &index) {
    if (!action) return true;

    if (action == playAction) {
        pieceView->setCurrentIndex(index);
    } else if (action == deleteAction) {
        pieceView->removeRow(index.row());
    } else {
        return false;
    }
    return true;
}

LibraryPieceMenu::LibraryPieceMenu(IPieceView *pieceView) :
    PieceMenu{pieceView},
    editAction{new QAction{tr("Edit"), this}} {

    addSeparator();
    addAction(editAction);
}

bool LibraryPieceMenu::apply(QAction *action, const QModelIndex &index) {
    if (PieceMenu::apply(action, index)) return true;

    const auto piece = pieceView->getPieceInRow(index.row());
    if (action == editAction) {
        auto dialog = new PieceEditDialog{pieceView, piece};
        dialog->show();
    } else {
        return false;
    }
    return true;
}
