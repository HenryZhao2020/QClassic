#include "SideBar.h"
#include "MainWindow.h"

#include <QHeaderView>

static constexpr int TypeRole{Qt::UserRole + 1};

SideBar::SideBar(MainWindow *win) : QTreeView{win} {
    header()->hide();

    model = new QStandardItemModel{this};
    setModel(model);

    composerRoot = new QStandardItem{tr("Composer")};
    composerRoot->setFlags(Qt::NoItemFlags);
    addItem("Ludwig Van Beethoven", ComposerItem);
    addItem("JS Bach", ComposerItem);
    addItem("Mozart", ComposerItem);
    model->appendRow(composerRoot);

    genreRoot = new QStandardItem{tr("Genre")};
    genreRoot->setFlags(Qt::NoItemFlags);
    addItem("String Quartet", GenreItem);
    addItem("Symphony", GenreItem);
    addItem("Sonata", GenreItem);
    model->appendRow(genreRoot);

    playlistRoot = new QStandardItem{tr("Playlist")};
    playlistRoot->setFlags(Qt::NoItemFlags);
    addItem("Bach's Lunch", PlaylistItem);
    model->appendRow(playlistRoot);

    connect(selectionModel(), &QItemSelectionModel::currentChanged,
            this, &SideBar::onItemSelected);

    expandAll();
}

QStandardItem *SideBar::addItem(const QString &text, Category type) {
    auto item = new QStandardItem{text};
    item->setData(type, TypeRole);

    switch (type) {
    case ComposerItem:
        composerRoot->appendRow(item);
        break;
    case GenreItem:
        genreRoot->appendRow(item);
        break;
    case PlaylistItem:
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
    case ComposerItem:
        qDebug() << "Composer selected:" << text;
        break;

    case GenreItem:
        qDebug() << "Genre selected:" << text;
        break;

    case PlaylistItem:
        qDebug() << "Playlist selected:" << text;
        break;

    default:
        qWarning() << "Unknown item selected:" << text;
        break;
    }
}
