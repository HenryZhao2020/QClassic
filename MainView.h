#pragma once

#include <QFrame>

class MainWindow;

class MainView : public QFrame {
    Q_OBJECT

public:
    MainView(MainWindow *win);
    ~MainView();
};
