#include "MainWindow.h"
#include "Playlist.h"
#include "Library.h"
#include "Composition.h"
#include "MenuBar.h"
#include "SideBar.h"
#include "PlayerBar.h"
#include "PlaylistView.h"

#include <QSplitter>
#include <QShortcut>
#include <QFileDialog>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent},
    openedFiles{new Playlist}, library{new Library},
    menuBar{new MenuBar{this}},
    sideBar{new SideBar{this}},
    playerBar{new PlayerBar{this}},
    treeView{new PlaylistView{this, openedFiles}} {

    auto splitter = new QSplitter{this};
    auto container = new QWidget{this};
    splitter->addWidget(sideBar);
    splitter->addWidget(container);
    splitter->setStretchFactor(1, 1);
    setCentralWidget(splitter);

    mainLayout = new QVBoxLayout{container};
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(playerBar, 0, Qt::AlignTop);
    mainLayout->addWidget(treeView, 1);

    resize(800, 600);

    // Use <Cmd+W> to close window in macOS
    auto *closeShortcut = new QShortcut{QKeySequence::Close, this};
    connect(closeShortcut, &QShortcut::activated, this, &QWidget::close);
}

MainWindow::~MainWindow() {
    delete openedFiles;
    delete library;
}

MenuBar *MainWindow::getMenuBar() const {
    return menuBar;
}

SideBar *MainWindow::getSideBar() const {
    return sideBar;
}

PlayerBar *MainWindow::getPlayerBar() const {
    return playerBar;
}

TreeView *MainWindow::getTreeView() const {
    return treeView;
}

void MainWindow::openFiles() {
    const QList<QUrl> urls{QFileDialog::getOpenFileUrls(this)};
    if (urls.isEmpty()) return;

    auto plistView = dynamic_cast<PlaylistView *>(treeView);

    Composition *composition{nullptr};
    QModelIndex index;
    for (const auto &url : urls) {
        composition = new Composition{url};
        index = plistView->addComposition(composition);
    }

    if (urls.size() == 1) {
        playerBar->setCurrentComposition(composition);
        plistView->setCurrentIndex(index);
    }
}

void MainWindow::setSideBarVisible(bool visible) {
    menuBar->showSideBarAction->setChecked(visible);
    sideBar->setVisible(visible);
}
