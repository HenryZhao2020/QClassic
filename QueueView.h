#pragma once

#include "IPieceView.h"

class Playlist;

class QueueView : public IPieceView {
    Q_OBJECT

public:
    QueueView(MainWindow *win, Playlist *queue);
};
