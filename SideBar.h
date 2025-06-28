#pragma once

#include <QFrame>
#include <QLineEdit>
#include <QTreeView>
#include <QStandardItem>
#include <QPushButton>

class MainWindow;
enum class Category;

class SideBar : public QFrame {
    Q_OBJECT

public:
    SideBar(MainWindow *win);

    QStandardItem *addItem(const QString &text, Category category);

private:
    QStandardItem *addRoot(const QString &text);
    void onItemSelected(const QModelIndex &current, const QModelIndex &);
    void showComposer();
    void searchMusic(const QString &text);

    MainWindow *win;
    QLineEdit *searchBar;
    QTreeView *tree;
    QStandardItemModel *model;
    QStandardItem *composerRoot;
    QStandardItem *genreRoot;
    QStandardItem *playlistRoot;
    QPushButton *importButton;

    bool filter{false};
    QHash<QStandardItem *, Qt::CheckState> itemStates;
};
