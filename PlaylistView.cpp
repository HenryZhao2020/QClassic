#include "PlaylistView.h"
#include "MainWindow.h"
#include "PlayerBar.h"
#include "Playlist.h"
#include "Composition.h"
#include "AppData.h"

PlaylistView::PlaylistView(MainWindow *win, Playlist *playlist)
    : TreeView{win}, win{win}, playlist{playlist}, currIndex{0} {

    setHeaders({tr("File Name"), tr("Duration")});
}

void PlaylistView::onDoubleClick(const QModelIndex &modelIndex) {
    currIndex = modelIndex.row();
    auto composition = playlist->getCompositions().at(currIndex);
    win->getPlayerBar()->setCurrentComposition(composition);
    win->getPlayerBar()->play();
}

void PlaylistView::setCurrentIndex(const QModelIndex &index) {
    currIndex = index.row();
    TreeView::setCurrentIndex(index);
}

QModelIndex PlaylistView::addComposition(Composition *composition) {
    auto item = addRow({composition->getTitle(),
                        composition->getDurationString()});
    playlist->addComposition(composition);
    connect(composition->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged,
            this, [this, item, composition] {
        item[1]->setText(composition->getDurationString());
        win->getPlayerBar()->updateDuration();
    });

    return getModel()->indexFromItem(item[0]);
}

void PlaylistView::selectPrev() {
    if (playlist->isEmpty()) return;

    // Repeat = One
    if (AppData::instance().getRepeat() == Repeat::One) {

    } else if (currIndex > 0) {
        --currIndex;
        setCurrentIndex(getModel()->index(currIndex, 0));
    }

    auto composition = playlist->getCompositions().at(currIndex);
    win->getPlayerBar()->setCurrentComposition(composition);
}

void PlaylistView::selectNext() {
    if (playlist->isEmpty()) return;

    if (AppData::instance().getRepeat() == Repeat::One) {
        // No change in index
    } else if (currIndex < playlist->size() - 1) {
        ++currIndex;
    } else if (AppData::instance().getRepeat() == Repeat::All) {
        currIndex = 0;
    } else {
        return;
    }

    setCurrentIndex(getModel()->index(currIndex, 0));
    auto composition = playlist->getCompositions().at(currIndex);
    win->getPlayerBar()->setCurrentComposition(composition);
}
