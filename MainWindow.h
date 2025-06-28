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

    void setMainContent(MainView *view);

    SideBar *getSideBar() const;

private:
    SideBar *sideBar{nullptr};
    QVBoxLayout *mainLayout{nullptr};
    PlayerBar *playerBar{nullptr};
    MainView *mainView{nullptr};
};
