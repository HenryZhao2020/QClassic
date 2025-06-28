#pragma once

#include "TreeView.h"

class MainWindow;

class ComposerView : public TreeView {
    Q_OBJECT

public:
    ComposerView(MainWindow *win);
};
