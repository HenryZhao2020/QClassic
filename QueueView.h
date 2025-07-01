#pragma once

#include "ICompositionView.h"

class Playlist;

class QueueView : public ICompositionView {
    Q_OBJECT

public:
    QueueView(MainWindow *win, Playlist *queue);
};
