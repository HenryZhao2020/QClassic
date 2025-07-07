#pragma once

#include <QMenu>

class IPieceView;

class PieceMenu : public QMenu {
    Q_OBJECT

    QAction *playAction;
    QAction *deleteAction;

protected:
    IPieceView *pieceView;

public:
    PieceMenu(IPieceView *pieceView);

    virtual bool apply(QAction *action, const QModelIndex &index);
};

class LibraryPieceMenu : public PieceMenu {
    Q_OBJECT

    QAction *editAction;

public:
    LibraryPieceMenu(IPieceView *pieceView);

    bool apply(QAction *action, const QModelIndex &index) override;
};
