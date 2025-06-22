#include "SideBar.h"
#include "MainWindow.h"

#include <QHeaderView>

static constexpr int TypeRole{Qt::UserRole + 1};

enum Category {
    Composer = 0,
    Genre,
    Playlist,
};

class ComposerRoot : public CategoryRoot {
public:
    ComposerRoot(SideBar *sideBar) : CategoryRoot{QObject::tr("Composer"), sideBar} {}

protected:
    void onItemSelected(const QModelIndex &current, const QModelIndex &) {
        auto item = model()->itemFromIndex(current);
        if (!item) return;

        Category type = static_cast<Category>(item->data(TypeRole).toInt());
        QString text = item->text();

        qDebug() << "Composer selected:" << text;
    }
};

CategoryRoot::CategoryRoot(const QString &text, SideBar *sideBar)
    : QStandardItem{text} {
    setFlags(Qt::NoItemFlags);
}

void CategoryRoot::addItem(const QString &text) {
    appendRow(new QStandardItem{text});
}

SideBar::SideBar(MainWindow *win)
    : QTreeView{win}, model{new QStandardItemModel{this}} {
    setModel(model);

    composerRoot = new ComposerRoot{this};
    composerRoot->addItem("Beethoven");
    composerRoot->addItem("Mozart");
    composerRoot->addItem("Haydn");
    model->appendRow(composerRoot);

    header()->hide();
    expandAll();
}
