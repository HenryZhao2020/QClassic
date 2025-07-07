#include "MainWindow.h"

#include "AppData.h"
#include "IPieceView.h"
#include "MenuBar.h"
#include "PlayerBar.h"
#include "Playback.h"
#include "SideBar.h"

#include <QActionGroup>

MenuBar::MenuBar(MainWindow *win) : QMenuBar{win}, win{win} {
    makeFileMenu();
    makeEditMenu();
    makeViewMenu();
    makeCtrlMenu();
}

void MenuBar::makeFileMenu() {
    auto openAction = new QAction{tr("Open Files..."), this};
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, win, &MainWindow::addToQueue);

    auto importAction = new QAction{tr("Import to Library"), this};
    importAction->setShortcut(Qt::CTRL | Qt::Key_I);
    connect(importAction, &QAction::triggered, win,
            &MainWindow::importLibrary);

    auto exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, win, &MainWindow::close);

    auto fileMenu = addMenu(tr("File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(importAction);
    fileMenu->addAction(exitAction);
}

void MenuBar::makeEditMenu() {}

void MenuBar::makeViewMenu() {
    auto sideBarAction = new QAction{tr("Show Side Bar"), this};
    sideBarAction->setCheckable(true);
    connect(sideBarAction, &QAction::triggered, this, [this](bool state) {
        win->getSideBar()->setVisible(state);
    });

    auto viewMenu = addMenu(tr("View"));
    viewMenu->addAction(sideBarAction);

    connect(viewMenu, &QMenu::aboutToShow, this, [=]() {
        sideBarAction->setChecked(win->getSideBar()->isVisible());
    });
}

void MenuBar::makeCtrlMenu() {
    auto playAction = new QAction{tr("Play"), this};
    playAction->setShortcut(Qt::Key_Space);
    connect(playAction, &QAction::triggered, this, [this]() {
        win->getPlayerBar()->playOrPause();
    });

    auto prevAction = new QAction{tr("Previous"), this};
    prevAction->setShortcut(Qt::Key_MediaPrevious);
    connect(prevAction, &QAction::triggered, this, [this]() {
        win->getPieceView()->selectPrev();
    });

    auto nextAction = new QAction{tr("Next"), this};
    nextAction->setShortcut(Qt::Key_MediaNext);
    connect(nextAction, &QAction::triggered, this, [this]() {
        win->getPieceView()->selectNext();
    });

    repeatMenu = new QMenu{tr("Repeat"), this};
    repeatGroup = new QActionGroup{repeatMenu};
    repeatGroup->setExclusive(true);
    addRepeatMode(tr("Off"), Repeat::Off);
    addRepeatMode(tr("All"), Repeat::All);
    addRepeatMode(tr("One"), Repeat::One);

    auto ctrlMenu = addMenu(tr("Controls"));
    ctrlMenu->addAction(playAction);
    ctrlMenu->addAction(prevAction);
    ctrlMenu->addAction(nextAction);
    ctrlMenu->addSeparator();
    ctrlMenu->addMenu(repeatMenu);

    connect(ctrlMenu, &QMenu::aboutToShow, this, [=]() {
        const bool enabled = win->getPlayerBar()->getCurrentPiece();
        playAction->setEnabled(enabled);
        prevAction->setEnabled(enabled);
        nextAction->setEnabled(enabled);
    });
}

void MenuBar::addRepeatMode(const QString &text, Repeat repeat) {
    auto repeatAction = new QAction{text, repeatGroup};
    repeatAction->setCheckable(true);
    repeatAction->setChecked(AppData::instance().getRepeat() == repeat);
    connect(repeatAction, &QAction::triggered, this, [repeat] {
        AppData::instance().setRepeat(repeat);
    });
    repeatMenu->addAction(repeatAction);
}
