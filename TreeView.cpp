#include "TreeView.h"
#include "MainWindow.h"

#include <QStandardItemModel>
#include <QHeaderView>

static constexpr int DEFAULT_COLUMN_COUNT{1};

TreeView::TreeView(MainWindow *win, const QStringList &headers)
    : QTreeView{win}, model{new QStandardItemModel{this}},
      columnCount{headers.isEmpty() ? DEFAULT_COLUMN_COUNT
                  : static_cast<int>(headers.size())} {

    model->setHorizontalHeaderLabels(headers);
    setModel(model);

    for (int i = 0; i < columnCount - 1; ++i) {
        header()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    header()->setStretchLastSection(columnCount == DEFAULT_COLUMN_COUNT);
    header()->setVisible(columnCount != DEFAULT_COLUMN_COUNT);
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
    return items;
}
