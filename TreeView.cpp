#include "TreeView.h"
#include "MainWindow.h"

#include <QStandardItemModel>
#include <QHeaderView>

TreeView::TreeView(MainWindow *win, const QStringList &headers)
    : QTreeView{win}, model{new QStandardItemModel{this}} {

    model->setHorizontalHeaderLabels(headers);
    setModel(model);

    header()->setSectionResizeMode(0, QHeaderView::Stretch);
    header()->setStretchLastSection(headers.isEmpty());
    header()->setVisible(!headers.isEmpty());
}

QStandardItemModel *TreeView::getModel() const {
    return model;
}

QStandardItem *TreeView::addSection(const QString &text) {
    auto section = new QStandardItem{text};
    section->setFlags(Qt::NoItemFlags);
    model->appendRow(section);
    resizeColumnToContents(0);  // Necessary for setting row height
    return section;
}

QStandardItem *TreeView::addRow(const QString &text, QStandardItem *section) {
    auto row = addRow(QStringList{text}, section);
    return row[0];
}

QList<QStandardItem *> TreeView::addRow(const QStringList &list,
                                        QStandardItem *section) {
    QList<QStandardItem *> items;
    for (const auto &text : list) {
        auto item = new QStandardItem{text};
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        items.append(item);
    }

    if (section) {
        section->appendRow(items);
        expandAll();
    } else {
        model->appendRow(items);
    }
    resizeColumnToContents(0);  // Necessary for setting row height

    return items;
}
