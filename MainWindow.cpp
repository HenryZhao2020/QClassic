#include "MainWindow.h"
#include "MenuBar.h"
#include "SideBar.h"
#include "PlayerBar.h"
#include "ICompositionView.h"
#include "QueueView.h"
#include "LibraryView.h"
#include "ImportDialog.h"
#include "Library.h"
#include "Playlist.h"
#include "Composition.h"
#include "AppData.h"

#include <QVBoxLayout>
#include <QScreen>
#include <QSplitter>
#include <QShortcut>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent},
    menuBar{new MenuBar{this}},
    sideBar{new SideBar{this}},
    playerBar{new PlayerBar{this}},
    playQueue{new Playlist},
    queueView{new QueueView{this, playQueue}},
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

    resize(900, 650);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    screen()->availableGeometry()));
    setSideBarVisible(AppData::instance().isSideBarVisible());

    // Use <Cmd+W> to close window in macOS
    auto closeShortcut = new QShortcut{QKeySequence::Close, this};
    connect(closeShortcut, &QShortcut::activated, this, &QWidget::close);
}

MainWindow::~MainWindow() {
    delete playQueue;
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

ICompositionView *MainWindow::getPlaylistView() const {
    return playlistView;
}

void MainWindow::setPlaylistView(Section section, Playlist *playlist) {
    if (playlistView) {
        mainLayout->removeWidget(playlistView);
        playlistView->hide();
    }

    if (section == Section::PlayQueue) {
        playlistView = queueView;
    } else if (section == Section::Library) {
        playlistView = libView;
    } else {
        playlistView = nullptr;
    }

    if (playlistView) {
        mainLayout->addWidget(playlistView, 1);
        playlistView->show();
        sideBar->setCurrentSection(section);
    }
}

void MainWindow::addToQueue() {
    const QList<QUrl> urls{QFileDialog::getOpenFileUrls(this)};
    if (urls.isEmpty()) return;

    for (const auto &url : urls) {
        queueView->addComposition(new Composition{url}, (urls.size() == 1));
    }
    setPlaylistView(Section::PlayQueue);
}

void MainWindow::importLibrary() {
    QUrl url{QFileDialog::getOpenFileUrl(this)};
    if (url.isEmpty()) return;

    auto dialog = new ImportDialog{libView, url};
    dialog->show();

    connect(dialog, &QDialog::finished, this, [this] (int) {
        setPlaylistView(Section::Library);
    });
}

void MainWindow::setSideBarVisible(bool visible) {
    menuBar->showSideBarAction->setChecked(visible);
    sideBar->setVisible(visible);
    AppData::instance().setSideBarVisible(visible);
}

void MainWindow::loadData() {
    auto lib = AppData::instance().getLibrary();
    for (auto composition : lib->getCompositions()) {
        libView->addComposition(composition);
    }
}
