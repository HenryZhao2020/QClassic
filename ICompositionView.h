#pragma once

#include "TreeView.h"

class MainWindow;
class Playlist;
class Composition;

class ICompositionView : public TreeView {
    Q_OBJECT

    MainWindow *win;
    Playlist *playlist;
    Composition *selectedComposition;
    int playingRowIndex;

protected:
    Composition *getCompositionAt(const QModelIndex &index);
    virtual void onSingleClick(const QModelIndex &index);
    virtual void onDoubleClick(const QModelIndex &index);
    virtual void onContextMenu(const QPoint &pos);
    virtual QList<QStandardItem *> addRow(Composition *composition) = 0;

public:
    ICompositionView(MainWindow *win, Playlist *playlist,
                     const QStringList &headers);

    void setCurrentIndex(const QModelIndex &index);
    void addComposition(Composition *composition, bool select = false);
    void removeRow(const QModelIndex &index);
    virtual void selectPrev();
    virtual void selectNext();
};
