#pragma once

#include "PlaylistView.h"

class MainWindow;
class Composer;

class ComposerView : public PlaylistView {
    Q_OBJECT

public:
    ComposerView(MainWindow *win, Composer *composer);
};
