#pragma once

#include <QFrame>

class MainWindow;

class SideBar : public QFrame {
    Q_OBJECT

public:
    SideBar(MainWindow *win);
};
