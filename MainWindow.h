#pragma once

#include <QMainWindow>

class QVBoxLayout;
class MenuBar;
class SideBar;
class PlayerBar;
class ICompositionView;
class QueueView;
class LibraryView;

class Playlist;
enum class Section;

class MainWindow : public QMainWindow {
    Q_OBJECT

    QVBoxLayout *mainLayout;
    MenuBar *menuBar;
    SideBar *sideBar;
    PlayerBar *playerBar;
    ICompositionView *playlistView;

    Playlist *playQueue;
    QueueView *queueView;
    LibraryView *libView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MenuBar *getMenuBar() const;
    SideBar *getSideBar() const;
    PlayerBar *getPlayerBar() const;
    ICompositionView *getPlaylistView() const;

    void setSideBarVisible(bool visible);
    void setPlaylistView(Section section, Playlist *playlist = nullptr);

    void addToQueue();
    void importLibrary();
};
