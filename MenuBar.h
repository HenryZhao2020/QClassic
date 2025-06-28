#pragma once

#include <QMenuBar>

class MainWindow;

class MenuBar : public QMenuBar {
    Q_OBJECT

    QAction *showSideBarAction;

public:
    MenuBar(MainWindow *win);

    friend MainWindow;
};
