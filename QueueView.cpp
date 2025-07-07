#include "QueueView.h"

#include "PieceViewType.h"
#include "Playlist.h"

QueueView::QueueView(MainWindow *win, Playlist *queue) :
    IPieceView{win, queue, PieceViewType::PlayQueue} {

    setColumnHidden(Column::Composer, true);
}
