#pragma once

#include "TreeView.h"

class MainWindow;

class SideBar : public TreeView {
    Q_OBJECT

public:
    SideBar(MainWindow *win);
};
