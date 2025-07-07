#pragma once

#include <QMainWindow>

class IPieceView;
class LibraryView;
class MenuBar;
class PlayerBar;
class Playlist;
class QueueView;
class SideBar;

class QVBoxLayout;

enum class PieceViewType;

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

    void setPieceView(PieceViewType type, Playlist *playlist = nullptr);
    void addToQueue();
    void importLibrary();
};
