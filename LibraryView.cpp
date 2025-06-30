#include "LibraryView.h"
#include "MainWindow.h"
#include "Library.h"
#include "Playlist.h"

LibraryView::LibraryView(MainWindow *win, Library *lib)
    : PlaylistView{win, Playlist::createPlaylist(lib->getCompositions()),
                   {tr("Title"), tr("Composer"), tr("Duration")}},
      win{win}, lib{lib} {}
