#include "MainWindow.h"
#include "SideBar.h"
#include "PlayerBar.h"
#include "MainView.h"

#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), sideBar{new SideBar{this}},
      playerBar{new PlayerBar{this}}, mainView{new MainView{this}} {
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
    mainLayout->addWidget(mainView, 1);
}

MainWindow::~MainWindow() {}
