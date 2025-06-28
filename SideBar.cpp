#include "SideBar.h"
#include "MainWindow.h"
#include "MainView.h"
#include "Library.h"
#include "ImportDialog.h"

#include <QHeaderView>
#include <QVBoxLayout>

static constexpr int TypeRole{Qt::UserRole + 1};

SideBar::SideBar(MainWindow *win) : QFrame{win}, win{win},
    searchBar{new QLineEdit{this}}, tree{new QTreeView{this}},
    model{new QStandardItemModel{this}},
    importButton{new QPushButton{tr("Import Music"), this}} {

    auto vboxLayout = new QVBoxLayout{this};
    vboxLayout->setSpacing(0);
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->addWidget(searchBar, 0);
    vboxLayout->addWidget(tree);
    vboxLayout->addWidget(importButton, 0);

    searchBar->setPlaceholderText("Search Music...");
    searchBar->setClearButtonEnabled(true);
    connect(searchBar, &QLineEdit::textChanged, this, &SideBar::searchMusic);

    tree->setModel(model);
    tree->header()->hide();

    addItem("Recent", Category::General);
    addItem("Music Library", Category::General);

    composerRoot = addRoot(tr("Composer"));
    // addItem("Ludwig Van Beethoven", Category::Composer);
    // addItem("JS Bach", Category::Composer);
    // addItem("Mozart", Category::Composer);

    genreRoot = addRoot(tr("Genre"));
    // addItem("String Quartet", Category::Genre);
    // addItem("Symphony", Category::Genre);
    // addItem("Sonata", Category::Genre);

    playlistRoot = addRoot(tr("Playlist"));
    // addItem("Bach's Lunch", Category::Playlist);

    connect(tree->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &SideBar::onItemSelected);
    connect(model, &QStandardItemModel::itemChanged, this, [this] (QStandardItem *item) {
        if (filter) {
            itemStates.insert(item, item->checkState());
        }
    });
    tree->expandAll();

    connect(importButton, &QPushButton::clicked, this, [win] {
        auto dialog = new ImportDialog{win};
        dialog->show();
    });
}

QStandardItem *SideBar::addRoot(const QString &text) {
    auto root = new QStandardItem{text};
    root->setFlags(Qt::NoItemFlags);
    model->appendRow(root);
    return root;
}

QStandardItem *SideBar::addItem(const QString &text, Category category) {
    auto item = new QStandardItem{text};
    item->setData(static_cast<int>(category), TypeRole);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
    itemStates.insert(item, Qt::Checked);

    switch (category) {
    case Category::Composer:
        composerRoot->appendRow(item);
        Library::instance().findComposer(text);
        break;
    case Category::Genre:
        genreRoot->appendRow(item);
        Library::instance().addGenre(new Genre{text});
        break;
    case Category::Playlist:
        playlistRoot->appendRow(item);
        Library::instance().addPlaylist(new Playlist{text});
        break;
    case Category::General:
        model->appendRow(item);
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
    case Category::Composer:
        win->setMainContent(new ComposerView{Library::instance().findComposer(text), win});
        qDebug() << "Composer selected:" << text;
        break;

    case Category::Genre:
        win->setMainContent(new GenreView{Library::instance().findGenre(text), win});
        qDebug() << "Genre selected:" << text;
        break;

    case Category::Playlist:
        win->setMainContent(new PlaylistView{Library::instance().findPlaylist(text), win});
        qDebug() << "Playlist selected:" << text;
        break;

    case Category::General:
        qWarning() << "Unknown item selected:" << text;
        break;
    }
}

void SideBar::searchMusic(const QString &text) {
    filter = !text.isEmpty();

    for (auto it = itemStates.begin(); it != itemStates.end(); ++it) {
        if (filter) {
            it.key()->setCheckState(it.value());
        } else {
            it.key()->setData(QVariant(), Qt::CheckStateRole);
        }
    }
}
