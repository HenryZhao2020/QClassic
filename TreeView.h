#pragma once

#include <QTreeView>
#include <QStandardItemModel>

class MainWindow;

class TreeView : public QTreeView {
    Q_OBJECT

    QStandardItemModel *model;
    int columnCount;

protected:
    QStandardItemModel *getModel() const;
    virtual void onDoubleClick(const QModelIndex &index);

public:
    TreeView(MainWindow *win);

    void setHeaders(const QStringList &headers);
    QStandardItem *addSection(const QString &text);
    QList<QStandardItem *> addRow(const QStringList &texts,
                                  QStandardItem *section = nullptr);

    virtual void selectPrev();
    virtual void selectNext();
};
