#pragma once

#include "TreeView.h"

class MainWindow;
class IPieceList;
class Piece;

class IPieceView : public TreeView {
    Q_OBJECT

    MainWindow *win;
    IPieceList *pieceList;
    Piece *selectedPiece;
    Piece *playingPiece;
    int playingRow;

protected:
    enum Column { Title = 0, Composer, Duration, PlayCount };

    IPieceView(MainWindow *win, IPieceList *list);

    QList<QStandardItem *> addRow(Piece *piece);
    void removeRow(int row);
    QList<QStandardItem *> getRow(Piece *piece) const;
    Piece *getPieceAtRow(int row) const;
    Piece *getSelectedPiece() const;

    void onSingleClick(const QModelIndex &index);
    void onDoubleClick(const QModelIndex &index);
    void onContextMenu(const QPoint &pos);

public:
    virtual ~IPieceView() = 0;

    void setCurrentIndex(const QModelIndex &index);
    void addPiece(Piece *piece, bool select = false);
    void increasePlayCount(Piece *piece);
    void selectPrev();
    void selectNext();
};
