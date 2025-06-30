#include "QueueView.h"
#include "Playlist.h"
#include "Composition.h"

QueueView::QueueView(MainWindow *win, Playlist *playlist) :
    PlaylistView{win, playlist, {tr("File Name"), tr("Duration")}} {}

QList<QStandardItem *> QueueView::addRow(Composition *composition) {
    return TreeView::addRow({composition->getName(),
                             composition->getDurationString()});
}
