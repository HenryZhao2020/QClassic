#pragma once

#include <QTreeView>
#include <QStandardItem>

class MainWindow;

class SideBar : public QTreeView {
    Q_OBJECT

public:
    SideBar(MainWindow *win);

private:
    enum Category {
        ComposerItem = 0,
        GenreItem,
        PlaylistItem,
    };

    QStandardItem *addItem(const QString &text, Category type);
    void onItemSelected(const QModelIndex &current, const QModelIndex &);

    QStandardItemModel *model;
    QStandardItem *composerRoot;
    QStandardItem *genreRoot;
    QStandardItem *playlistRoot;
};
