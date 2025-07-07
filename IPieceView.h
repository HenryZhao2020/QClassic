#pragma once

#include "TreeView.h"

class IPieceList;
class MainWindow;
class Piece;
class PieceMenu;

enum class PieceViewType;

class IPieceView : public TreeView {
    Q_OBJECT

    MainWindow *win;
    IPieceList *pieceList;
    int playingRow;
    Piece *selectedPiece;
    PieceMenu *contextMenu;

protected:
    enum Column { Title = 0, Composer, Duration, PlayCount };

    IPieceView(MainWindow *win, IPieceList *list, PieceViewType type);

    QList<QStandardItem *> addRow(Piece *piece);
    QList<QStandardItem *> getRow(Piece *piece) const;

    void onSingleClick(const QModelIndex &index);
    void onDoubleClick(const QModelIndex &index);
    void onContextMenu(const QPoint &pos);

public:
    virtual ~IPieceView() = 0;

    // Override TreeView::setCurrentIndex
    void setCurrentIndex(const QModelIndex &index);

    void addPiece(Piece *piece, bool select = false);
    void updatePiece(Piece *piece);
    Piece *getPieceInRow(int row) const;
    Piece *getSelectedPiece() const;

    void removeRow(int row);

    void selectPrev();
    void selectNext();
};
