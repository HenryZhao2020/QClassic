#include "MainWindow.h"
#include "MenuBar.h"
#include "SideBar.h"
#include "PlayerBar.h"
#include "PlaylistView.h"
#include "LibraryView.h"
#include "ComposerView.h"
#include "Playlist.h"
#include "Composition.h"
#include "AppData.h"

#include <QVBoxLayout>
#include <QSplitter>
#include <QShortcut>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent},
    openedFiles{new Playlist},
    menuBar{new MenuBar{this}},
    sideBar{new SideBar{this}},
    playerBar{new PlayerBar{this}},
    filesView{new PlaylistView{this, openedFiles}},
    libView{new LibraryView{this, AppData::instance().getLibrary()}},
    playlistView{nullptr} {

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

    resize(800, 600);
    setSideBarVisible(AppData::instance().isSideBarVisible());

    // Use <Cmd+W> to close window in macOS
    auto closeShortcut = new QShortcut{QKeySequence::Close, this};
    connect(closeShortcut, &QShortcut::activated, this, &QWidget::close);
}

MainWindow::~MainWindow() {
    delete openedFiles;
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

PlaylistView *MainWindow::getPlaylistView() const {
    return filesView;
}

void MainWindow::setPlaylistView(Section section) {
    if (playlistView) {
        mainLayout->removeWidget(playlistView);
        playlistView->hide();
    }

    if (section == Section::OpenedFiles) {
        playlistView = filesView;
    } else if (section == Section::Library) {
        playlistView = libView;
    } else {
        playlistView = nullptr;
    }

    if (playlistView) {
        mainLayout->addWidget(playlistView, 1);
        playlistView->show();               // ensure it's made visible
        playlistView->update();             // force redraw
        mainLayout->update();               // update layout itself
        mainLayout->invalidate();           // trigger layout recalculation
        sideBar->setCurrentSection(section);
    }
}

void MainWindow::setComposerView(Composer *composer) {
    ComposerView *composerView{nullptr};
    if (!composerViewMap.contains(composer)) {
        composerView = new ComposerView{this, composer};
        composerViewMap.insert(composer, composerView);
    } else {
        composerViewMap.value(composer);
    }

    if (playlistView) {
        mainLayout->removeWidget(playlistView);
    }
    mainLayout->addWidget(composerView, 1);
}

void MainWindow::openFiles() {
    const QList<QUrl> urls{QFileDialog::getOpenFileUrls(this)};
    if (urls.isEmpty()) return;

    QModelIndex index;
    for (const auto &url : urls) {
        index = filesView->addComposition(new Composition{url});
    }

    if (urls.size() == 1) {
        filesView->setCurrentIndex(index);
    }

    setPlaylistView(Section::OpenedFiles);
}

void MainWindow::setSideBarVisible(bool visible) {
    menuBar->showSideBarAction->setChecked(visible);
    sideBar->setVisible(visible);
    AppData::instance().setSideBarVisible(visible);
}
