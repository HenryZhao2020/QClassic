#include "MainView.h"
#include "MainWindow.h"
#include "Library.h"

#include <QHeaderView>

MainView::MainView(MainWindow *win)
    : QTreeView{win}, model{new QStandardItemModel{this}} {
    setModel(model);

    header()->hide();
    expandAll();
}

ComposerView::ComposerView(Composer *composer, MainWindow *win) : MainView{win} {
    model->appendRow(new QStandardItem{composer->getName()});
}

GenreView::GenreView(Genre *genre, MainWindow *win) : MainView{win} {
    model->appendRow(new QStandardItem{genre->getName()});
}

PlaylistView::PlaylistView(Playlist *playlist, MainWindow *win) : MainView{win} {
    model->appendRow(new QStandardItem{playlist->getName()});
}
