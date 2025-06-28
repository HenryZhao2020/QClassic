#pragma once

#include <QMainWindow>
#include <QVBoxLayout>

class Library;
class Playlist;

class MenuBar;
class SideBar;
class PlayerBar;
class TreeView;

class MainWindow : public QMainWindow {
    Q_OBJECT

    Library *lib;
    Playlist *tempPlaylist;

    QVBoxLayout *mainLayout;
    MenuBar *menuBar;
    SideBar *sideBar;
    PlayerBar *playerBar;
    TreeView *mainView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SideBar *getSideBar() const;
    PlayerBar *getPlayerBar() const;
    TreeView *getMainView() const;

    void openFile();
    void setSideBarVisible(bool visible);
};
