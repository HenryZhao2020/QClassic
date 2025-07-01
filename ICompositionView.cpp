#include "ICompositionView.h"
#include "MainWindow.h"
#include "PlayerBar.h"
#include "ICompositionList.h"
#include "Composition.h"
#include "AppData.h"

#include <QMediaPlayer>
#include <QTimer>
#include <QMenu>
#include <QMessageBox>

ICompositionView::ICompositionView(MainWindow *win, ICompositionList *list) :
    TreeView{win, {tr("Title"), tr("Composer"), tr("Duration"), tr("Play Count")}},
    win{win}, list{list}, playingRowIndex{0} {

    connect(this, &ICompositionView::clicked, this,
            &ICompositionView::onSingleClick);
    connect(this, &ICompositionView::doubleClicked, this,
            &ICompositionView::onDoubleClick);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this,
            &ICompositionView::onContextMenu);
}

ICompositionView::~ICompositionView() {}

QList<QStandardItem *> ICompositionView::addRow(Composition *composition) {
    Q_ASSERT(composition);
    auto row = TreeView::addRow({
        composition->getName(),
        composition->getComposer(),
        composition->getDurationString(),
        QString::number(composition->getPlayCount()),
    });

    void *data = composition;
    row[Column::Title]->setData(QVariant::fromValue(data), Qt::UserRole);

    connect(composition->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged,
            this, [this, row, composition] {
        auto durationItem = row[Column::Duration];
        durationItem->setText(composition->getDurationString());
        win->getPlayerBar()->updateDuration();
    });

    return row;
}

void ICompositionView::removeRow(int row) {
    win->getPlayerBar()->setCurrentComposition(nullptr);
    if (list->removeComposition(getCompositionAtRow(row))) {
        getModel()->removeRow(row);
    }

    auto newIndex = currentIndex();
    if (newIndex.isValid()) {
        win->getPlayerBar()->setCurrentComposition(getCompositionAtRow(newIndex.row()));
    }
}

QList<QStandardItem *> ICompositionView::getRow(Composition *composition) {
    int rowCount{getModel()->rowCount()};
    for (int row = 0; row < rowCount; ++row) {
        if (getCompositionAtRow(row) == composition) {
            return TreeView::getRow(row);
        }
    }
    return {};
}

Composition *ICompositionView::getCompositionAtRow(int row) {
    auto item = getModel()->index(row, Column::Title);
    void *data = item.data(Qt::UserRole).value<void *>();
    return static_cast<Composition *>(data);
}

void ICompositionView::onSingleClick(const QModelIndex &index) {
    selectedComposition = getCompositionAtRow(index.row());
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
        removeRow(index.row());
    }
}

void ICompositionView::setCurrentIndex(const QModelIndex &index) {
    playingRowIndex = index.row();
    auto composition = getCompositionAtRow(index.row());
    win->getPlayerBar()->setCurrentComposition(composition);
    TreeView::setCurrentIndex(index);
}

void ICompositionView::addComposition(Composition *composition, bool select) {
    Q_ASSERT(composition);
    list->addComposition(composition);

    auto row = addRow(composition);

    QTimer::singleShot(0, this, [this] { setFocus(); });
    QModelIndex index{getModel()->indexFromItem(row[Column::Title])};
    if (select) setCurrentIndex(index);
}

void ICompositionView::incrementPlayCount(Composition *composition) {
    int newCount{composition->getPlayCount() + 1};
    composition->setPlayCount(newCount);

    auto row = getRow(composition);
    row[Column::PlayCount]->setText(QString::number(newCount));
}

void ICompositionView::selectPrev() {
    if (list->isEmpty()) return;

    if (AppData::instance().getRepeat() != Repeat::One && playingRowIndex > 0) {
        --playingRowIndex;
    }

    setCurrentIndex(getModel()->index(playingRowIndex, Column::Title));
}

void ICompositionView::selectNext() {
    if (list->isEmpty()) return;

    auto repeat = AppData::instance().getRepeat();
    if (playingRowIndex < list->size() - 1 && repeat != Repeat::One) {
        ++playingRowIndex;
    } else if (repeat == Repeat::All) {
        playingRowIndex = 0;
    } else if (repeat == Repeat::Off) {
        return;
    }

    setCurrentIndex(getModel()->index(playingRowIndex, Column::Title));
}
