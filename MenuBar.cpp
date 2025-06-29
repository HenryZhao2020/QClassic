#include "MenuBar.h"
#include "MainWindow.h"
#include "PlayerBar.h"
#include "PlaylistView.h"
#include "AppData.h"

MenuBar::MenuBar(MainWindow *win) : QMenuBar{win} {
    auto fileMenu = addMenu(tr("File"));
    auto editMenu = addMenu(tr("Edit"));
    auto viewMenu = addMenu(tr("View"));
    auto ctrlMenu = addMenu(tr("Controls"));

    auto openAction = new QAction{tr("Open Music Files..."), this};
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, win, &MainWindow::openFiles);
    fileMenu->addAction(openAction);

    auto exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, win, &MainWindow::close);
    fileMenu->addAction(exitAction);

    auto cutAction = new QAction{tr("Cut"), this};
    cutAction->setShortcut(QKeySequence::Cut);
    editMenu->addAction(cutAction);

    auto copyAction = new QAction{tr("Copy"), this};
    copyAction->setShortcut(QKeySequence::Copy);
    editMenu->addAction(copyAction);

    auto pasteAction = new QAction{tr("Paste"), this};
    pasteAction->setShortcut(QKeySequence::Paste);
    editMenu->addAction(pasteAction);

    showSideBarAction = new QAction{tr("Show Side Bar"), this};
    showSideBarAction->setCheckable(true);
    connect(showSideBarAction, &QAction::triggered,
            win, &MainWindow::setSideBarVisible);
    viewMenu->addAction(showSideBarAction);

    playAction = new QAction{tr("Play"), this};
    playAction->setShortcut(Qt::Key_Space);
    connect(playAction, &QAction::triggered, this,
            [win] { win->getPlayerBar()->playOrPause(); });
    ctrlMenu->addAction(playAction);

    prevAction = new QAction{tr("Previous"), this};
    prevAction->setShortcut(Qt::Key_MediaPrevious);
    connect(prevAction, &QAction::triggered, this,
            [win] { win->getPlaylistView()->selectPrev(); });
    ctrlMenu->addAction(prevAction);

    nextAction = new QAction{tr("Next"), this};
    nextAction->setShortcut(Qt::Key_MediaNext);
    connect(nextAction, &QAction::triggered, this,
            [win] { win->getPlaylistView()->selectNext(); });
    ctrlMenu->addAction(nextAction);

    repeatOffAction = new QAction{tr("Off"), this};
    repeatOffAction->setCheckable(true);
    connect(repeatOffAction, &QAction::triggered, this, [this] {
        setRepeat(Repeat::Off);
    });

    repeatAllAction = new QAction{tr("All"), this};
    repeatAllAction->setCheckable(true);
    connect(repeatAllAction, &QAction::triggered, this, [this] {
        setRepeat(Repeat::All);
    });

    repeatOneAction = new QAction{tr("One"), this};
    repeatOneAction->setCheckable(true);
    connect(repeatOneAction, &QAction::triggered, this, [this] {
        setRepeat(Repeat::One);
    });

    auto repeatMenu = ctrlMenu->addMenu(tr("Repeat"));
    repeatMenu->addAction(repeatOffAction);
    repeatMenu->addAction(repeatAllAction);
    repeatMenu->addAction(repeatOneAction);
    setRepeat(AppData::instance().getRepeat());

    addMenu(fileMenu);
    addMenu(editMenu);
    addMenu(viewMenu);
    addMenu(ctrlMenu);
}

void MenuBar::setRepeat(Repeat repeat) {
    AppData::instance().setRepeat(repeat);
    repeatOffAction->setChecked(repeat == Repeat::Off);
    repeatAllAction->setChecked(repeat == Repeat::All);
    repeatOneAction->setChecked(repeat == Repeat::One);
}
