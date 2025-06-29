#include "SideBar.h"
#include "MainWindow.h"

#include <QHeaderView>

SideBar::SideBar(MainWindow *win) : TreeView{win} {
    header()->setVisible(false);
    header()->setSectionResizeMode(QHeaderView::Stretch);

    addRow(tr("Opened Files"));
    addRow(tr("Library"));

    auto composerSection = addSection(tr("Composer"));
    addRow(tr("Haydn"), composerSection);
    addRow(tr("Bach"), composerSection);
    addRow(tr("Beethoven"), composerSection);
}
