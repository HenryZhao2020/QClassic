#include "PlaylistView.h"
#include "MainWindow.h"
#include "PlayerBar.h"
#include "Playlist.h"
#include "Composition.h"

PlaylistView::PlaylistView(MainWindow *win, Playlist *playlist)
    : TreeView{win}, win{win}, playlist{playlist}, currIndex{0} {

    setHeaders({tr("Title"), tr("Duration")});
}

void PlaylistView::onDoubleClick(const QModelIndex &modelIndex) {
    currIndex = modelIndex.row();
    auto composition = playlist->getCompositions().at(currIndex);
    win->getPlayerBar()->setCurrentComposition(composition);
    win->getPlayerBar()->play();
}

void PlaylistView::addComposition(Composition *composition) {
    playlist->addComposition(composition);
    currIndex = playlist->size() - 1;

    connect(composition->getMediaPlayer(), &QMediaPlayer::mediaStatusChanged,
            this, [this, composition] {
        auto item = addRow({composition->getTitle(), composition->getDurationFormat()});
        setCurrentIndex(getModel()->indexFromItem(item[0]));
        disconnect(composition->getMediaPlayer(),
                   &QMediaPlayer::mediaStatusChanged,
                   nullptr, nullptr);
    });
}

void PlaylistView::selectPrev() {
    if (playlist->isEmpty()) return;

    auto composition = playlist->getCompositions().at(currIndex);
    if (currIndex > 0) {
        --currIndex;
        setCurrentIndex(getModel()->index(currIndex, 0));
    }
    win->getPlayerBar()->setCurrentComposition(composition);
}

void PlaylistView::selectNext() {
    if (playlist->isEmpty()) return;

    if (currIndex < playlist->size() - 1) {
        ++currIndex;
        setCurrentIndex(getModel()->index(currIndex, 0));
        win->getPlayerBar()->setCurrentComposition(playlist->getCompositions().at(currIndex));
    }
}
