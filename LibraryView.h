#pragma once

#include "ICompositionView.h"

class Library;

class LibraryView : public ICompositionView {
    Q_OBJECT

    MainWindow *win;
    Library *lib;

protected:
    QList<QStandardItem *> addRow(Composition *composition) override;

public:
    LibraryView(MainWindow *win, Library *lib);
};
