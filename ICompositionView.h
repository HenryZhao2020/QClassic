#pragma once

#include "TreeView.h"

class MainWindow;
class ICompositionList;
class Composition;

class ICompositionView : public TreeView {
    Q_OBJECT

    MainWindow *win;
    ICompositionList *list;
    Composition *selectedComposition;
    int playingRowIndex;

protected:
    enum Column { Title = 0, Composer, Duration };

    QList<QStandardItem *> addRow(Composition *composition);
    void removeRow(const QModelIndex &index);
    Composition *getCompositionAt(const QModelIndex &index);

    void onSingleClick(const QModelIndex &index);
    void onDoubleClick(const QModelIndex &index);
    void onContextMenu(const QPoint &pos);

public:
    ICompositionView(MainWindow *win, ICompositionList *list);
    virtual ~ICompositionView() = 0;

    void setCurrentIndex(const QModelIndex &index);
    void addComposition(Composition *composition, bool select = false);
    void selectPrev();
    void selectNext();
};
