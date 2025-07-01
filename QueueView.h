#pragma once

#include "ICompositionView.h"

class Playlist;

class QueueView : public ICompositionView {
    Q_OBJECT

protected:
    QList<QStandardItem *> addRow(Composition *composition) override;

public:
    QueueView(MainWindow *win, Playlist *queue);
};
