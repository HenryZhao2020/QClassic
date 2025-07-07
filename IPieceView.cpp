#include "IPieceView.h"

#include "AppData.h"
#include "IPieceList.h"
#include "MainWindow.h"
#include "Piece.h"
#include "PieceEditor.h"
#include "PieceMenu.h"
#include "PieceViewType.h"
#include "Playback.h"
#include "PlayerBar.h"

#include <QMediaPlayer>

IPieceView::IPieceView(MainWindow *win, IPieceList *list, PieceViewType type) :
    TreeView{win, {tr("Title"), tr("Composer"),
                   tr("Duration"), tr("Play Count")}},
    win{win}, pieceList{list}, playingRow{0}, selectedPiece{nullptr},
    contextMenu{(type == PieceViewType::PlayQueue) ? new PieceMenu{this}
                : new LibraryPieceMenu{this}} {

    connect(this, &IPieceView::clicked, this, &IPieceView::onSingleClick);
    connect(this, &IPieceView::doubleClicked, this,
            &IPieceView::onDoubleClick);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this,
            &IPieceView::onContextMenu);
}

IPieceView::~IPieceView() {}

QList<QStandardItem *> IPieceView::addRow(Piece *piece) {
    Q_ASSERT(piece);
    auto row = TreeView::addRow({
        piece->getName(),
        piece->getComposer(),
        piece->getDurationString(),
        QString::number(piece->getPlayCount()),
    });

    const auto rowData = QVariant::fromValue(static_cast<void *>(piece));
    row[Column::Title]->setData(rowData, Qt::UserRole);

    connect(piece->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged, this,
            [this, row, piece]() {
        row[Column::Duration]->setText(piece->getDurationString());
        win->getPlayerBar()->updateDuration();
    });

    return row;
}

QList<QStandardItem *> IPieceView::getRow(Piece *piece) const {
    const int rowCount{getModel()->rowCount()};
    for (int row = 0; row < rowCount; ++row) {
        if (getPieceInRow(row) == piece) {
            return TreeView::getRow(row);
        }
    }
    return {};
}

void IPieceView::onSingleClick(const QModelIndex &index) {
    selectedPiece = getPieceInRow(index.row());
}

void IPieceView::onDoubleClick(const QModelIndex &modelIndex) {
    if (modelIndex.isValid()) {
        setCurrentIndex(modelIndex);
    }
}

void IPieceView::onContextMenu(const QPoint &pos) {
    const QModelIndex index{indexAt(pos)};
    if (!index.isValid()) return;

    const QPoint screenPos{viewport()->mapToGlobal(pos)};
    const auto selectedAction = contextMenu->exec(screenPos);
    contextMenu->apply(selectedAction, index);
}

void IPieceView::setCurrentIndex(const QModelIndex &index) {
    if (!index.isValid()) return;

    const int row{index.row()};
    playingRow = row;
    win->getPlayerBar()->setCurrentPiece(getPieceInRow(row));
    TreeView::setCurrentIndex(index);
}

void IPieceView::addPiece(Piece *piece, bool select) {
    Q_ASSERT(piece);
    pieceList->addPiece(piece);

    const auto row = addRow(piece);
    if (select) {
        setCurrentIndex(getModel()->indexFromItem(row.front()));
    }
    setFocus();
}

void IPieceView::updatePiece(Piece *piece) {
    auto row = getRow(piece);
    row[Column::Title]->setText(piece->getName());
    row[Column::Composer]->setText(piece->getComposer());
    row[Column::Duration]->setText(piece->getDurationString());
    row[Column::PlayCount]->setText(QString::number(piece->getPlayCount()));
}

Piece *IPieceView::getPieceInRow(int row) const {
    const auto item = getModel()->index(row, Column::Title);
    return static_cast<Piece *>(item.data(Qt::UserRole).value<void *>());
}

Piece *IPieceView::getSelectedPiece() const {
    return selectedPiece;
}

void IPieceView::removeRow(int row) {
    win->getPlayerBar()->setCurrentPiece(nullptr);
    if (pieceList->removePiece(getPieceInRow(row))) {
        getModel()->removeRow(row);
    }
    setCurrentIndex(currentIndex());
}

void IPieceView::selectPrev() {
    if (pieceList->isEmpty()) return;

    const Repeat repeat{AppData::instance().getRepeat()};
    if (repeat != Repeat::One && playingRow > 0) {
        --playingRow;
    }

    setCurrentIndex(getModel()->index(playingRow, Column::Title));
}

void IPieceView::selectNext() {
    if (pieceList->isEmpty()) return;

    const Repeat repeat{AppData::instance().getRepeat()};
    if (playingRow < pieceList->size() - 1 && repeat != Repeat::One) {
        ++playingRow;
    } else if (repeat == Repeat::All) {
        playingRow = 0;
    } else if (repeat == Repeat::Off) {
        return;
    }

    setCurrentIndex(getModel()->index(playingRow, Column::Title));
}
