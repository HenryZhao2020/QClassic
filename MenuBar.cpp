#include "MenuBar.h"
#include "MainWindow.h"

MenuBar::MenuBar(MainWindow *win) : QMenuBar{win} {
    auto fileMenu = addMenu(tr("File"));
    auto editMenu = addMenu(tr("Edit"));
    auto viewMenu = addMenu(tr("View"));
    auto ctrlMenu = addMenu(tr("Control"));

    auto openAction = new QAction{tr("Open Music File..."), this};
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, win, &MainWindow::openFile);
    fileMenu->addAction(openAction);

    auto exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, &QAction::triggered, win, &MainWindow::close);
    fileMenu->addAction(exitAction);

    auto cutAction = new QAction{tr("Cut"), this};
    editMenu->addAction(cutAction);

    auto copyAction = new QAction{tr("Copy"), this};
    editMenu->addAction(copyAction);

    auto pasteAction = new QAction{tr("Paste"), this};
    editMenu->addAction(pasteAction);

    showSideBarAction = new QAction{tr("Show Side Bar"), this};
    showSideBarAction->setCheckable(true);
    connect(showSideBarAction, &QAction::triggered,
            win, &MainWindow::setSideBarVisible);
    viewMenu->addAction(showSideBarAction);

    auto playAction = new QAction{tr("Play"), this};
    ctrlMenu->addAction(playAction);

    addMenu(fileMenu);
    addMenu(editMenu);
    addMenu(viewMenu);
    addMenu(ctrlMenu);
}
