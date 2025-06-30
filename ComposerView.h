#pragma once

#include "PlaylistView.h"

class Library;
class Composer;

class ComposerView : public PlaylistView {
    Q_OBJECT

    MainWindow *win;
    Composer *composer;

public:
    ComposerView(MainWindow *win, Composer *composer);
};
