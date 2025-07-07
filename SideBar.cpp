#include "SideBar.h"

#include "MainWindow.h"
#include "PieceViewType.h"

SideBar::SideBar(MainWindow *win) : TreeView{win}, win{win} {
    setFocusPolicy(Qt::NoFocus);

    auto queueSection = addRow(tr("Play Queue"));
    queueSection->setData(QVariant::fromValue(PieceViewType::PlayQueue),
                          Qt::UserRole);

    auto libSection = addRow(tr("Library"));
    libSection->setData(QVariant::fromValue(PieceViewType::Library),
                        Qt::UserRole);

    // auto playlistSection = addSection(tr("Playlist"));
    // addRow("Bach's Lunch", playlistSection);

    connect(selectionModel(), &QItemSelectionModel::currentChanged,
            this, &SideBar::onSelection);
}

void SideBar::onSelection(const QModelIndex &current, const QModelIndex &) {
    const auto item = getModel()->itemFromIndex(current);
    if (item) {
        win->setPieceView(PieceViewType{item->data(Qt::UserRole).toInt()});
    }
}

void SideBar::setCurrentSection(PieceViewType type) {
    const int rowCount{getModel()->rowCount()};
    for (int i = 0; i < rowCount; ++i) {
        const auto item = getModel()->item(i);
        if (!item) continue;

        if (type == PieceViewType{item->data(Qt::UserRole).toInt()}) {
            const QModelIndex index{getModel()->indexFromItem(item)};
            setCurrentIndex(index);
            scrollTo(index);
            break;
        }
    }
}
