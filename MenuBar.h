#pragma once

#include <QMenuBar>
#include <QAction>

class MainWindow;
class PlayerBar;
enum class Repeat;

class MenuBar : public QMenuBar {
    Q_OBJECT

    QAction *showSideBarAction;

    QAction *playAction;
    QAction *prevAction;
    QAction *nextAction;

    QAction *repeatOffAction;
    QAction *repeatAllAction;
    QAction *repeatOneAction;

    void setRepeat(Repeat repeat);

public:
    MenuBar(MainWindow *win);

    friend MainWindow;
    friend PlayerBar;
};
