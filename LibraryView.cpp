#include "LibraryView.h"
#include "MainWindow.h"
#include "Library.h"

LibraryView::LibraryView(MainWindow *win, Library *lib) :
    IPieceView{win, lib} {

    for (const auto &piece : lib->getPieces()) {
        addRow(piece);
    }
}
