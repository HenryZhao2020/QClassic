#pragma once

#include <QFrame>

class MainWindow;

class PlayerBar : public QFrame {
    Q_OBJECT

public:
    PlayerBar(MainWindow *win);
};
