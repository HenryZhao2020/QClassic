#pragma once

#include "PlaylistView.h"

class Playlist;

class QueueView : public PlaylistView {
    Q_OBJECT

protected:
    QList<QStandardItem *> addRow(Composition *composition) override;

public:
    QueueView(MainWindow *win, Playlist *queue);
};
