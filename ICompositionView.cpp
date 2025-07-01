#include "ICompositionView.h"
#include "MainWindow.h"
#include "PlayerBar.h"
#include "Playlist.h"
#include "Composition.h"
#include "AppData.h"

#include <QMediaPlayer>
#include <QTimer>
#include <QMenu>

static constexpr int DATA_COLUMN{0};

ICompositionView::ICompositionView(MainWindow *win, Playlist *playlist,
    const QStringList &headers) : TreeView{win, headers}, win{win},
    playlist{playlist}, playingRowIndex{0} {

    connect(this, &ICompositionView::clicked, this, &ICompositionView::onSingleClick);
    connect(this, &ICompositionView::doubleClicked, this,
            &ICompositionView::onDoubleClick);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this,
            &ICompositionView::onContextMenu);
}

Composition *ICompositionView::getCompositionAt(const QModelIndex &index) {
    auto item = getModel()->index(index.row(), DATA_COLUMN);
    void *data = item.data(Qt::UserRole).value<void *>();
    return static_cast<Composition *>(data);
}

void ICompositionView::onSingleClick(const QModelIndex &index) {
    selectedComposition = getCompositionAt(index);
}

void ICompositionView::onDoubleClick(const QModelIndex &modelIndex) {
    setCurrentIndex(modelIndex);
    win->getPlayerBar()->play();
}

void ICompositionView::onContextMenu(const QPoint &pos) {
    QModelIndex index = indexAt(pos);
    if (!index.isValid()) return;

    QMenu contextMenu{this};
    auto editAction = contextMenu.addAction(tr("Edit"));
    auto deleteAction = contextMenu.addAction(tr("Delete"));

    auto selectedAction = contextMenu.exec(viewport()->mapToGlobal(pos));
    if (!selectedAction) return;

    if (selectedAction == editAction) {
        // handle open
    } else if (selectedAction == deleteAction) {
        removeRow(index);
    }
}

void ICompositionView::setCurrentIndex(const QModelIndex &index) {
    playingRowIndex = index.row();
    auto composition = playlist->getCompositions().at(playingRowIndex);
    win->getPlayerBar()->setCurrentComposition(composition);
    TreeView::setCurrentIndex(index);
}

void ICompositionView::addComposition(Composition *composition, bool select) {
    Q_ASSERT(composition);
    playlist->addComposition(composition);

    auto row = addRow(composition);
    row[DATA_COLUMN]->setData(
        QVariant::fromValue(static_cast<void *>(composition)),
        Qt::UserRole);
    connect(composition->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged,
            this, [this, row, composition] {
        auto durationItem = row.back();
        durationItem->setText(composition->getDurationString());
        win->getPlayerBar()->updateDuration();
    });

    QTimer::singleShot(0, this, [this] { setFocus(); });
    QModelIndex index{getModel()->indexFromItem(row[DATA_COLUMN])};
    if (select) setCurrentIndex(index);
}

void ICompositionView::removeRow(const QModelIndex &index) {
    playlist->removeComposition(getCompositionAt(index));
    getModel()->removeRow(index.row());
}

void ICompositionView::selectPrev() {
    // if (playlist->isEmpty()) return;

    if (AppData::instance().getRepeat() != Repeat::One && playingRowIndex > 0) {
        --playingRowIndex;
    }

    setCurrentIndex(getModel()->index(playingRowIndex, DATA_COLUMN));
}

void ICompositionView::selectNext() {
    if (playlist->isEmpty()) return;

    auto repeat = AppData::instance().getRepeat();
    if (playingRowIndex < playlist->size() - 1 && repeat != Repeat::One) {
        ++playingRowIndex;
    } else if (repeat == Repeat::All) {
        playingRowIndex = 0;
    } else if (repeat == Repeat::Off) {
        return;
    }

    setCurrentIndex(getModel()->index(playingRowIndex, DATA_COLUMN));
}
