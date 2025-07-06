#pragma once

#include <QMainWindow>

class QVBoxLayout;
class MenuBar;
class SideBar;
class PlayerBar;
class IPieceView;
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
    IPieceView *pieceView;

    Playlist *playQueue;
    QueueView *queueView;
    LibraryView *libView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MenuBar *getMenuBar() const;
    SideBar *getSideBar() const;
    PlayerBar *getPlayerBar() const;
    IPieceView *getPieceView() const;

    void setPieceView(Section section, Playlist *playlist = nullptr);
    void addToQueue();
    void importLibrary();
};
