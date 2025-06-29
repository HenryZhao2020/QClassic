#include "TreeView.h"
#include "MainWindow.h"
#include <QHeaderView>

TreeView::TreeView(MainWindow *win)
    : QTreeView{win}, model{new QStandardItemModel{this}}, columnCount{1} {

    setModel(model);
    connect(this, &TreeView::doubleClicked, this, &TreeView::onDoubleClick);
    header()->setStretchLastSection(false);
}

QStandardItemModel *TreeView::getModel() const {
    return model;
}

void TreeView::onDoubleClick(const QModelIndex &index) {}

void TreeView::setHeaders(const QStringList &headers) {
    model->setHorizontalHeaderLabels(headers);
    columnCount = headers.size();

    for (int i = 0; i < columnCount - 1; ++i) {
        header()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

QStandardItem *TreeView::addSection(const QString &text) {
    auto section = new QStandardItem{text};
    section->setFlags(Qt::NoItemFlags);
    model->appendRow(section);
    resizeColumnToContents(0);

    for (int i = 1; i < columnCount; ++i) {
        auto filler = new QStandardItem;
        filler->setFlags(Qt::NoItemFlags);
        model->appendRow(filler);
    }

    return section;
}

QStandardItem *TreeView::addRow(const QString &text, QStandardItem *section) {
    auto item = new QStandardItem{text};
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    if (section) {
        section->appendRow(item);
    } else {
        model->appendRow(item);
    }

    return item;
}

QList<QStandardItem *> TreeView::addRow(const QStringList &texts, QStandardItem *section) {
    QList<QStandardItem *> items;
    for (const auto &text : texts) {
        auto item = new QStandardItem{text};
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        items.append(item);
    }

    if (section) {
        section->appendRow(items);
    } else {
        model->appendRow(items);
    }
    return items;
}

void TreeView::selectPrev() {}

void TreeView::selectNext() {}
