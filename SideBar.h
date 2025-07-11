#pragma once

#include "TreeView.h"

class MainWindow;

enum class PieceViewType;

class SideBar : public TreeView {
    Q_OBJECT

    MainWindow *win;

    void onSelection(const QModelIndex &current, const QModelIndex &);

public:
    SideBar(MainWindow *win);

    void setCurrentSection(PieceViewType type);
};
