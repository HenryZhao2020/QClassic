#include "ComposerView.h"
#include "MainWindow.h"
#include "Library.h"
#include "Composer.h"
#include "Playlist.h"

ComposerView::ComposerView(MainWindow *win, Composer *composer)
    : PlaylistView{win, Playlist::createPlaylist(composer->getCompositions()),
                   {tr("Title"), tr("Duration")}},
      win{win}, composer{composer} {}
