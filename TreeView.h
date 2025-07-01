#pragma once

#include <QTreeView>
#include <QStandardItem>
#include <QStringList>

class QStandardItemModel;
class MainWindow;

class TreeView : public QTreeView {
    Q_OBJECT

    QStandardItemModel *model;

protected:
    QStandardItemModel *getModel() const;

public:
    TreeView(MainWindow *win, const QStringList &headers = {});

    QStandardItem *addSection(const QString &text);
    QStandardItem *addRow(const QString &text,
                          QStandardItem *section = nullptr);
    QList<QStandardItem *> addRow(const QStringList &list,
                                  QStandardItem *section = nullptr);
    QList<QStandardItem *> getRow(int row) const;
};
