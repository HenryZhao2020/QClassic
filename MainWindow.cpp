#include "MainWindow.h"

#include "AppData.h"
#include "IPieceView.h"
#include "Library.h"
#include "LibraryView.h"
#include "MenuBar.h"
#include "Piece.h"
#include "PieceEditor.h"
#include "PieceViewType.h"
#include "PlayerBar.h"
#include "Playlist.h"
#include "QueueView.h"
#include "SideBar.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QShortcut>
#include <QSplitter>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent},
    menuBar{new MenuBar{this}},
    sideBar{new SideBar{this}},
    playerBar{new PlayerBar{this}},
    playQueue{new Playlist},
    queueView{new QueueView{this, playQueue}},
    libView{new LibraryView{this, AppData::instance().getLibrary()}},
    pieceView{nullptr} {

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

    const bool libEmpty{AppData::instance().getLibrary()->isEmpty()};
    setPieceView(libEmpty ? PieceViewType::PlayQueue
                          : PieceViewType::Library);

    resize(900, 650);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    size(), screen()->availableGeometry()));

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

IPieceView *MainWindow::getPieceView() const {
    return pieceView;
}

void MainWindow::setPieceView(PieceViewType type, Playlist *playlist) {
    if (pieceView) {
        mainLayout->removeWidget(pieceView);
        pieceView->hide();
    }

    if (type == PieceViewType::PlayQueue) {
        pieceView = queueView;
    } else if (type == PieceViewType::Library) {
        pieceView = libView;
    }

    if (pieceView) {
        mainLayout->addWidget(pieceView, 1);
        pieceView->show();
        sideBar->setCurrentSection(type);
    }
}

void MainWindow::addToQueue() {
    const QList<QUrl> urls{QFileDialog::getOpenFileUrls(this)};
    if (urls.isEmpty()) return;

    setPieceView(PieceViewType::PlayQueue);
    for (const auto &url : urls) {
        queueView->addPiece(new Piece{url}, (urls.size() == 1));
    }
}

void MainWindow::importLibrary() {
    const QUrl url{QFileDialog::getOpenFileUrl(this)};
    if (url.isEmpty()) return;

    auto lib = AppData::instance().getLibrary();
    if (Piece piece{url}; lib->containsPiece(&piece)) {
        QMessageBox::critical(this, "Duplicate Item",
                              "Piece already exists in the library!");
        return;
    }

    setPieceView(PieceViewType::Library);

    auto dialog = new PieceImportDialog{libView, url};
    dialog->show();
}
