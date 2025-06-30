#include "SideBar.h"
#include "MainWindow.h"

static constexpr int SectionRole{Qt::UserRole + 1};

SideBar::SideBar(MainWindow *win) : TreeView{win}, win{win} {
    auto filesSection = addRow(tr("Opened Files"));
    filesSection->setData(QVariant::fromValue(Section::OpenedFiles));

    auto libSection = addRow(tr("Library"));
    libSection->setData(QVariant::fromValue(Section::Library));

    auto composerSection = addSection(tr("Composer"));
    addRow(tr("Haydn"), composerSection);
    addRow(tr("Bach"), composerSection);
    addRow(tr("Beethoven"), composerSection);

    connect(selectionModel(), &QItemSelectionModel::currentChanged,
            this, &SideBar::onSelection);
}

void SideBar::onSelection(const QModelIndex &current, const QModelIndex &) {
    auto item = getModel()->itemFromIndex(current);
    if (!item) return;

    Section section = static_cast<Section>(item->data().toInt());
    QString text = item->text();

    switch (section) {
    case Section::OpenedFiles:
        qDebug() << "Opened Files Selected";
        win->setPlaylistView(Section::OpenedFiles);
        break;

    case Section::Library:
        qDebug() << "Library Selected";
        win->setPlaylistView(Section::Library);
        break;

    case Section::Composer:
        qDebug() << "Composer Selected: " << text;
        break;

    default:
        qWarning() << "Unknown item selected:" << text;
        break;
    }
}

void SideBar::setCurrentSection(Section section) {
    for (int row = 0; row < getModel()->rowCount(); ++row) {
        QStandardItem *item = getModel()->item(row);
        if (!item) continue;

        QVariant var = item->data();
        if (var.canConvert<Section>() && var.value<Section>() == section) {
            QModelIndex index = getModel()->index(row, 0);
            this->setCurrentIndex(index);
            this->scrollTo(index);
            return;
        }
    }
}
