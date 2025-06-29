#include "ComposerView.h"
#include "Composer.h"

ComposerView::ComposerView(MainWindow *win, Composer *composer)
    : PlaylistView{win, composer->getPlaylist()} {}
