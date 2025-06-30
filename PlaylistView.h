#pragma once

#include "TreeView.h"

class MainWindow;
class Playlist;
class Composition;

class PlaylistView : public TreeView {
    Q_OBJECT

    MainWindow *win;
    Playlist *playlist;
    Composition *selectedComposition;
    int playingRowIndex;

protected:
    Composition *getCompositionAt(const QModelIndex &index);
    virtual void onSingleClick(const QModelIndex &index);
    virtual void onDoubleClick(const QModelIndex &index);
    virtual QList<QStandardItem *> addRow(Composition *composition) = 0;

public:
    PlaylistView(MainWindow *win, Playlist *playlist,
                 const QStringList &headers);

    void setCurrentIndex(const QModelIndex &index);
    QModelIndex addComposition(Composition *composition);
    virtual void selectPrev();
    virtual void selectNext();
};
