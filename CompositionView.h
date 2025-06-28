#pragma once

#include "TreeView.h"

class MainWindow;

class CompositionView : public TreeView {
    Q_OBJECT

public:
    CompositionView(MainWindow *win);
};
