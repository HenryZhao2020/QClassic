#pragma once

#include "TreeView.h"

class MainWindow;
class Playlist;
class Composition;

class PlaylistView : public TreeView {
    Q_OBJECT

    MainWindow *win;
    Playlist *playlist;
    int currIndex;

protected:
    void onDoubleClick(const QModelIndex &modelIndex) override;

public:
    PlaylistView(MainWindow *win, Playlist *playlist);

    void setCurrentIndex(const QModelIndex &index);
    QModelIndex addComposition(Composition *composition);
    void selectPrev() override;
    void selectNext() override;
};
