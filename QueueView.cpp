#include "QueueView.h"
#include "Playlist.h"

QueueView::QueueView(MainWindow *win, Playlist *queue) :
    IPieceView{win, queue} {

    setColumnHidden(Column::Composer, true);
}
