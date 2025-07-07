#include "LibraryView.h"

#include "Library.h"
#include "MainWindow.h"
#include "PieceViewType.h"

LibraryView::LibraryView(MainWindow *win, Library *lib) :
    IPieceView{win, lib, PieceViewType::Library} {

    for (const auto &piece : lib->getPieces()) {
        addRow(piece);
    }
}
