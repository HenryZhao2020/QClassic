#include "SideBar.h"
#include "MainWindow.h"

SideBar::SideBar(MainWindow *win) : TreeView{win}, win{win} {
    setFocusPolicy(Qt::NoFocus);

    auto queueSection = addRow(tr("Play Queue"));
    queueSection->setData(QVariant::fromValue(Section::PlayQueue));

    auto libSection = addRow(tr("Library"));
    libSection->setData(QVariant::fromValue(Section::Library));

    // auto playlistSection = addSection(tr("Playlist"));
    // addRow("Bach's Lunch", playlistSection);

    connect(selectionModel(), &QItemSelectionModel::currentChanged,
            this, &SideBar::onSelection);
}

void SideBar::onSelection(const QModelIndex &current, const QModelIndex &) {
    const auto item = getModel()->itemFromIndex(current);
    if (!item) return;

    Section section{item->data().toInt()};
    win->setPieceView(section);
}

void SideBar::setCurrentSection(Section section) {
    const int rowCount{getModel()->rowCount()};
    for (int i = 0; i < rowCount; ++i) {
        const auto item = getModel()->item(i);
        if (!item) continue;

        if (section == static_cast<Section>(item->data().toInt())) {
            QModelIndex index{getModel()->indexFromItem(item)};
            setCurrentIndex(index);
            scrollTo(index);
            break;
        }
    }
}
