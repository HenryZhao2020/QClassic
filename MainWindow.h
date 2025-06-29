#pragma once

#include <QMainWindow>
#include <QVBoxLayout>

class Playlist;
class Library;

class MenuBar;
class SideBar;
class PlayerBar;
class TreeView;

class MainWindow : public QMainWindow {
    Q_OBJECT

    Playlist *openedFiles;
    Library *library;

    QVBoxLayout *mainLayout;
    MenuBar *menuBar;
    SideBar *sideBar;
    PlayerBar *playerBar;
    TreeView *treeView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MenuBar *getMenuBar() const;
    SideBar *getSideBar() const;
    PlayerBar *getPlayerBar() const;
    TreeView *getTreeView() const;

    void openFiles();
    void setSideBarVisible(bool visible);
};
