#include "LibraryView.h"
#include "MainWindow.h"
#include "Library.h"

LibraryView::LibraryView(MainWindow *win, Library *lib) :
    ICompositionView{win, lib} {

    for (auto c : lib->getCompositions()) {
        addRow(c);
    }
}
