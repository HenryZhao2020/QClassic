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
        Composer = 0,
        Genre,
        Playlist,
    };

    QStandardItem *addRoot(const QString &text);
    QStandardItem *addItem(const QString &text, Category cat);
    void onItemSelected(const QModelIndex &current, const QModelIndex &);
    void showComposer();

    QStandardItemModel *model;
    QStandardItem *composerRoot;
    QStandardItem *genreRoot;
    QStandardItem *playlistRoot;
};
