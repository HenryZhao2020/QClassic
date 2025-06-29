#pragma once

#include <QMainWindow>

class Playlist;
class QVBoxLayout;
class MenuBar;
class SideBar;
class PlayerBar;
class PlaylistView;

class MainWindow : public QMainWindow {
    Q_OBJECT

    Playlist *openedFiles;

    QVBoxLayout *mainLayout;
    MenuBar *menuBar;
    SideBar *sideBar;
    PlayerBar *playerBar;
    PlaylistView *playlistView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MenuBar *getMenuBar() const;
    SideBar *getSideBar() const;
    PlayerBar *getPlayerBar() const;
    PlaylistView *getPlaylistView() const;

    void openFiles();
    void setSideBarVisible(bool visible);
};
