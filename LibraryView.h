#pragma once

#include "ICompositionView.h"

class Library;

class LibraryView : public ICompositionView {
    Q_OBJECT

public:
    LibraryView(MainWindow *win, Library *lib);
};
