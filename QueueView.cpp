#include "QueueView.h"
#include "Playlist.h"

QueueView::QueueView(MainWindow *win, Playlist *playlist) :
    ICompositionView{win, playlist} {

    setColumnHidden(Column::Composer, true);
}
