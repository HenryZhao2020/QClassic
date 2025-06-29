#include "PlaylistView.h"
#include "MainWindow.h"
#include "PlayerBar.h"
#include "Playlist.h"
#include "Composition.h"
#include "AppData.h"

#include <QMediaPlayer>

static constexpr int DATA_COLUMN{0};
static constexpr int DURATION_COLUMN{1};

PlaylistView::PlaylistView(MainWindow *win, Playlist *playlist,
                          const QStringList &headers)
    : TreeView{win, headers}, win{win}, playlist{playlist}, currPlaying{0} {

    connect(this, &PlaylistView::clicked, this, &PlaylistView::onSingleClick);
    connect(this, &PlaylistView::doubleClicked, this,
            &PlaylistView::onDoubleClick);
}

void PlaylistView::onSingleClick(const QModelIndex &index) {
    Composition *c = getCompositionAt(index);
    qDebug() << "Selected: " << c->getName();
}

void PlaylistView::onDoubleClick(const QModelIndex &modelIndex) {
    setCurrentIndex(modelIndex);
    win->getPlayerBar()->play();
}

QList<QStandardItem *> PlaylistView::addRow(Composition *composition) {
    return TreeView::addRow({composition->getName(),
                             composition->getDurationString()});
}

Composition *PlaylistView::getCompositionAt(const QModelIndex &index) {
    auto item = getModel()->index(index.row(), DATA_COLUMN);
    void *data = item.data(Qt::UserRole).value<void *>();
    return static_cast<Composition *>(data);
}

void PlaylistView::setCurrentIndex(const QModelIndex &index) {
    currPlaying = index.row();
    auto composition = playlist->getCompositions().at(currPlaying);
    win->getPlayerBar()->setCurrentComposition(composition);
    TreeView::setCurrentIndex(index);
}

QModelIndex PlaylistView::addComposition(Composition *composition) {
    Q_ASSERT(composition);
    playlist->addComposition(composition);

    auto row = addRow(composition);
    row[DATA_COLUMN]->setData(
        QVariant::fromValue(static_cast<void *>(composition)),
        Qt::UserRole);
    connect(composition->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged,
            this, [this, row, composition] {
        auto durationItem = row[DURATION_COLUMN];
        durationItem->setText(composition->getDurationString());
        win->getPlayerBar()->updateDuration();
    });

    setFocus();
    return getModel()->indexFromItem(row[DATA_COLUMN]);
}

void PlaylistView::selectPrev() {
    if (playlist->isEmpty()) return;

    if (AppData::instance().getRepeat() != Repeat::One && currPlaying > 0) {
        --currPlaying;
    }

    setCurrentIndex(getModel()->index(currPlaying, DATA_COLUMN));
}

void PlaylistView::selectNext() {
    if (playlist->isEmpty()) return;

    auto repeat = AppData::instance().getRepeat();
    if (currPlaying < playlist->size() - 1 && repeat != Repeat::One) {
        ++currPlaying;
    } else if (repeat == Repeat::All) {
        currPlaying = 0;
    } else if (repeat == Repeat::Off) {
        return;
    }

    setCurrentIndex(getModel()->index(currPlaying, DATA_COLUMN));
}
