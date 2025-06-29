#pragma once

#include "TreeView.h"

class MainWindow;
class Playlist;
class Composition;

class PlaylistView : public TreeView {
    Q_OBJECT

    MainWindow *win;
    Playlist *playlist;
    int currPlaying;

protected:
    virtual void onSingleClick(const QModelIndex &index);
    virtual void onDoubleClick(const QModelIndex &index);
    virtual QList<QStandardItem *> addRow(Composition *composition);
    Composition *getCompositionAt(const QModelIndex &index);

public:
    PlaylistView(MainWindow *win, Playlist *playlist,
                 const QStringList &headers = {tr("File Name"),
                                               tr("Duration")});

    void setCurrentIndex(const QModelIndex &index);
    QModelIndex addComposition(Composition *composition);

    virtual void selectPrev();
    virtual void selectNext();
};
