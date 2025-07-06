#pragma once

#include "IPieceView.h"

class Library;

class LibraryView : public IPieceView {
    Q_OBJECT

public:
    LibraryView(MainWindow *win, Library *lib);
};
