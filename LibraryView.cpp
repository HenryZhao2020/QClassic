#include "LibraryView.h"
#include "MainWindow.h"
#include "Library.h"
#include "Playlist.h"
#include "Composition.h"

LibraryView::LibraryView(MainWindow *win, Library *lib) :
    ICompositionView{win, Playlist::createPlaylist(lib->getCompositions()),
                 {tr("Title"), tr("Composer"), tr("Duration")}},
    win{win}, lib{lib} {}

QList<QStandardItem *> LibraryView::addRow(Composition *composition) {
    return TreeView::addRow({composition->getName(),
                             composition->getComposer(),
                             composition->getDurationString()});
}
