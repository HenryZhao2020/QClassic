#include "SideBar.h"
#include "MainWindow.h"

SideBar::SideBar(MainWindow *win) : TreeView{win} {
    addRow(tr("Opened Files"));
    addRow(tr("Library"));

    auto composerSection = addSection(tr("Composer"));
    addRow(tr("Haydn"), composerSection);
    addRow(tr("Bach"), composerSection);
    addRow(tr("Beethoven"), composerSection);
}
