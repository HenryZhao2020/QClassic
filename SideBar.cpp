#include "SideBar.h"
#include "MainWindow.h"

#include <QHeaderView>

static constexpr int TypeRole{Qt::UserRole + 1};

SideBar::SideBar(MainWindow *win) : QTreeView{win} {
    model = new QStandardItemModel{this};
    setModel(model);

    composerRoot = addRoot(tr("Composer"));
    addItem("Ludwig Van Beethoven", Composer);
    addItem("JS Bach", Composer);
    addItem("Mozart", Composer);

    genreRoot = addRoot(tr("Genre"));
    addItem("String Quartet", Genre);
    addItem("Symphony", Genre);
    addItem("Sonata", Genre);

    playlistRoot = addRoot(tr("Playlist"));
    addItem("Bach's Lunch", Playlist);

    connect(selectionModel(), &QItemSelectionModel::currentChanged,
            this, &SideBar::onItemSelected);

    header()->hide();
    expandAll();
}

QStandardItem *SideBar::addRoot(const QString &text) {
    auto root = new QStandardItem{text};
    root->setFlags(Qt::NoItemFlags);
    model->appendRow(root);
    return root;
}

QStandardItem *SideBar::addItem(const QString &text, Category cat) {
    auto item = new QStandardItem{text};
    item->setData(cat, TypeRole);

    switch (cat) {
    case Composer:
        composerRoot->appendRow(item);
        break;
    case Genre:
        genreRoot->appendRow(item);
        break;
    case Playlist:
        playlistRoot->appendRow(item);
        break;
    }

    return item;
}

void SideBar::onItemSelected(const QModelIndex &current, const QModelIndex &) {
    auto item = model->itemFromIndex(current);
    if (!item) return;

    Category type = static_cast<Category>(item->data(TypeRole).toInt());
    QString text = item->text();

    switch (type) {
    case Composer:
        qDebug() << "Composer selected:" << text;
        break;

    case Genre:
        qDebug() << "Genre selected:" << text;
        break;

    case Playlist:
        qDebug() << "Playlist selected:" << text;
        break;

    default:
        qWarning() << "Unknown item selected:" << text;
        break;
    }
}
