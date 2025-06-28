#pragma once

#include <QTreeView>
#include <QStandardItem>

class MainWindow;
class Composer;
class Genre;
class Playlist;

class MainView : public QTreeView {
    Q_OBJECT

public:
    MainView(MainWindow *win);

protected:
    QStandardItemModel *model;
};

class ComposerView : public MainView {
    Q_OBJECT

public:
    ComposerView(Composer *composer, MainWindow *win);
};

class GenreView : public MainView {
    Q_OBJECT

public:
    GenreView(Genre *genre, MainWindow *win);
};

class PlaylistView : public MainView {
    Q_OBJECT

public:
    PlaylistView(Playlist *playlist, MainWindow *win);
};
