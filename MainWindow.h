#pragma once

#include <QMainWindow>
#include <QVBoxLayout>

class SideBar;
class PlayerBar;
class MainView;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    SideBar *sideBar;
    QVBoxLayout *mainLayout;
    PlayerBar *playerBar;
    MainView *mainView;
};
