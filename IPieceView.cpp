#include "IPieceView.h"
#include "MainWindow.h"
#include "PlayerBar.h"
#include "IPieceList.h"
#include "Piece.h"
#include "AppData.h"
#include "Playback.h"

#include <QMediaPlayer>
#include <QTimer>
#include <QMenu>

IPieceView::IPieceView(MainWindow *win, IPieceList *list) :
    TreeView{win, {tr("Title"), tr("Composer"),
                   tr("Duration"), tr("Play Count")}},
    win{win}, pieceList{list}, playingRow{0} {

    connect(this, &IPieceView::clicked, this,
            &IPieceView::onSingleClick);
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

    connect(piece->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged,
            this, [this, row, piece] {
        row[Column::Duration]->setText(piece->getDurationString());
        win->getPlayerBar()->updateDuration();
    });

    return row;
}

void IPieceView::removeRow(int row) {
    win->getPlayerBar()->setCurrentPiece(nullptr);
    if (pieceList->removePiece(getPieceAtRow(row))) {
        getModel()->removeRow(row);
    }
    setCurrentIndex(currentIndex());
}

QList<QStandardItem *> IPieceView::getRow(Piece *piece) const {
    const int rowCount{getModel()->rowCount()};
    for (int row = 0; row < rowCount; ++row) {
        if (getPieceAtRow(row) == piece) {
            return TreeView::getRow(row);
        }
    }
    return {};
}

Piece *IPieceView::getPieceAtRow(int row) const {
    const auto item = getModel()->index(row, Column::Title);
    return static_cast<Piece *>(item.data(Qt::UserRole).value<void *>());
}

Piece *IPieceView::getSelectedPiece() const {
    return selectedPiece;
}

void IPieceView::onSingleClick(const QModelIndex &index) {
    selectedPiece = getPieceAtRow(index.row());
}

void IPieceView::onDoubleClick(const QModelIndex &modelIndex) {
    if (!modelIndex.isValid()) return;

    setCurrentIndex(modelIndex);
    win->getPlayerBar()->play();
}

void IPieceView::onContextMenu(const QPoint &pos) {
    const QModelIndex index{indexAt(pos)};
    if (!index.isValid()) return;

    QMenu contextMenu{this};
    const int row{index.row()};
    const auto selectedPiece = getPieceAtRow(row);
    const bool playing{playingPiece == selectedPiece};

    auto playAction = contextMenu.addAction(playing ? tr("Pause") : tr("Play"));
    auto deleteAction = contextMenu.addAction(tr("Delete"));

    auto selectedAction = contextMenu.exec(viewport()->mapToGlobal(pos));
    if (!selectedAction) return;
    if (selectedAction == playAction) {
        if (playing) win->getPlayerBar()->pause();
        else setCurrentIndex(index);
    } else if (selectedAction == deleteAction) {
        removeRow(row);
    }
}

void IPieceView::setCurrentIndex(const QModelIndex &index) {
    if (!index.isValid()) return;

    const int row{index.row()};
    playingRow = row;
    playingPiece = getPieceAtRow(row);
    win->getPlayerBar()->setCurrentPiece(playingPiece);
    TreeView::setCurrentIndex(index);
}

void IPieceView::addPiece(Piece *piece, bool select) {
    Q_ASSERT(piece);
    pieceList->addPiece(piece);

    const auto row = addRow(piece);
    QTimer::singleShot(0, this, [this] { setFocus(); });

    if (select) {
        setCurrentIndex(getModel()->indexFromItem(row.front()));
    }
}

void IPieceView::increasePlayCount(Piece *piece) {
    const int newCount{piece->getPlayCount() + 1};
    piece->setPlayCount(newCount);

    auto row = getRow(piece);
    row[Column::PlayCount]->setText(QString::number(newCount));
}

void IPieceView::selectPrev() {
    if (pieceList->isEmpty()) return;

    Repeat repeat{AppData::instance().getRepeat()};
    if (repeat != Repeat::One && playingRow > 0) {
        --playingRow;
    }

    setCurrentIndex(getModel()->index(playingRow, Column::Title));
}

void IPieceView::selectNext() {
    if (pieceList->isEmpty()) return;

    Repeat repeat{AppData::instance().getRepeat()};
    if (playingRow < pieceList->size() - 1 && repeat != Repeat::One) {
        ++playingRow;
    } else if (repeat == Repeat::All) {
        playingRow = 0;
    } else if (repeat == Repeat::Off) {
        return;
    }

    setCurrentIndex(getModel()->index(playingRow, Column::Title));
}
