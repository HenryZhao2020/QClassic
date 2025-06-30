#pragma once

#include "PlaylistView.h"

class Library;

class LibraryView : public PlaylistView {
    Q_OBJECT

    MainWindow *win;
    Library *lib;

public:
    LibraryView(MainWindow *win, Library *lib);
};
