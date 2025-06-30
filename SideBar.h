#pragma once

#include "TreeView.h"

class MainWindow;

enum class Section { PlayQueue = 1, Library, Playlist };

class SideBar : public TreeView {
    Q_OBJECT

    MainWindow *win;

    void onSelection(const QModelIndex &current, const QModelIndex &);

public:
    SideBar(MainWindow *win);

    void setCurrentSection(Section section);
};
