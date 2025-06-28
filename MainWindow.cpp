#include "MainWindow.h"
#include "SideBar.h"
#include "PlayerBar.h"
#include "MainView.h"

#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), sideBar{new SideBar{this}},
      playerBar{new PlayerBar{this}} {
    resize(800, 600);

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
}

void MainWindow::setMainContent(MainView *view) {
    if (mainView) {
        mainLayout->removeWidget(mainView);
        mainView->deleteLater();
    }

    if (view) {
        mainLayout->addWidget(view, 1);
    }
    mainView = view;
}

SideBar *MainWindow::getSideBar() const {
    return sideBar;
}
