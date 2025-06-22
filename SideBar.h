#pragma once

#include <QTreeView>
#include <QStandardItem>

class MainWindow;
class CategoryRoot;

class SideBar : public QTreeView {
    Q_OBJECT

public:
    SideBar(MainWindow *win);
    QStandardItemModel *getModel() const { return model; };

private:
    QStandardItemModel *model;
    CategoryRoot *composerRoot;
};

class CategoryRoot : public QStandardItem {
public:
    CategoryRoot(const QString &text, SideBar *sideBar);

    virtual void addItem(const QString &text);

protected:
    virtual void onItemSelected(const QModelIndex &current, const QModelIndex &) = 0;
};
