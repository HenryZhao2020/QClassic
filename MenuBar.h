#pragma once

#include <QMenuBar>
#include <QAction>

class MainWindow;
class PlayerBar;

class MenuBar : public QMenuBar {
    Q_OBJECT

    QAction *showSideBarAction;
    QAction *playAction;
    QAction *prevAction;
    QAction *nextAction;

public:
    MenuBar(MainWindow *win);

    friend MainWindow;
    friend PlayerBar;
};
