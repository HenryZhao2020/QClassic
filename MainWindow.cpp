#include "MainWindow.h"
#include "Composition.h"
#include "Library.h"
#include "MenuBar.h"
#include "SideBar.h"
#include "PlayerBar.h"
#include "TreeView.h"
#include "PlaylistView.h"
#include "Playlist.h"

#include <QSplitter>
#include <QShortcut>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent},
    lib{new Library}, tempPlaylist{new Playlist},
    menuBar{new MenuBar{this}}, sideBar{new SideBar{this}},
    playerBar{new PlayerBar{this}},
    mainView{new PlaylistView{this, tempPlaylist}} {

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
    mainLayout->addWidget(mainView, 1);

    resize(550, 650);
    setSideBarVisible(false);

    // Use <Cmd+W> to close window in macOS
    auto *closeShortcut = new QShortcut{QKeySequence::Close, this};
    connect(closeShortcut, &QShortcut::activated, this, &QWidget::close);
}

MainWindow::~MainWindow() {
    delete tempPlaylist;
}

SideBar *MainWindow::getSideBar() const {
    return sideBar;
}

PlayerBar *MainWindow::getPlayerBar() const {
    return playerBar;
}

TreeView *MainWindow::getMainView() const {
    return mainView;
}

void MainWindow::openFile() {
    QUrl url = QFileDialog::getOpenFileUrl(this);
    if (url.isEmpty()) return;

    auto plistView = dynamic_cast<PlaylistView *>(mainView);
    auto composition = new Composition{url.path()};
    plistView->addComposition(composition);
    playerBar->setCurrentComposition(composition);
}

void MainWindow::setSideBarVisible(bool visible) {
    menuBar->showSideBarAction->setChecked(visible);
    sideBar->setVisible(visible);
}
