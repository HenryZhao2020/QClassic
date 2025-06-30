#include "PlaylistView.h"
#include "MainWindow.h"
#include "PlayerBar.h"
#include "Playlist.h"
#include "Composition.h"
#include "AppData.h"

#include <QMediaPlayer>
#include <QTimer>

static constexpr int DATA_COLUMN{0};

PlaylistView::PlaylistView(MainWindow *win, Playlist *playlist,
                          const QStringList &headers)
    : TreeView{win, headers}, win{win}, playlist{playlist}, playingRowIndex{0} {

    connect(this, &PlaylistView::clicked, this, &PlaylistView::onSingleClick);
    connect(this, &PlaylistView::doubleClicked, this,
            &PlaylistView::onDoubleClick);
}

Composition *PlaylistView::getCompositionAt(const QModelIndex &index) {
    auto item = getModel()->index(index.row(), DATA_COLUMN);
    void *data = item.data(Qt::UserRole).value<void *>();
    return static_cast<Composition *>(data);
}

void PlaylistView::onSingleClick(const QModelIndex &index) {
    selectedComposition = getCompositionAt(index);
}

void PlaylistView::onDoubleClick(const QModelIndex &modelIndex) {
    setCurrentIndex(modelIndex);
    win->getPlayerBar()->play();
}

void PlaylistView::setCurrentIndex(const QModelIndex &index) {
    playingRowIndex = index.row();
    auto composition = playlist->getCompositions().at(playingRowIndex);
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
        auto durationItem = row.back();
        durationItem->setText(composition->getDurationString());
        win->getPlayerBar()->updateDuration();
    });

    QTimer::singleShot(0, this, [this] { setFocus(); });
    return getModel()->indexFromItem(row[DATA_COLUMN]);
}

void PlaylistView::selectPrev() {
    if (playlist->isEmpty()) return;

    if (AppData::instance().getRepeat() != Repeat::One && playingRowIndex > 0) {
        --playingRowIndex;
    }

    setCurrentIndex(getModel()->index(playingRowIndex, DATA_COLUMN));
}

void PlaylistView::selectNext() {
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
