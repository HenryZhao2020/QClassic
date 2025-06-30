#pragma once

#include <QMainWindow>
#include <QMap>

class Playlist;
class Composer;
class QVBoxLayout;
class MenuBar;
class SideBar;
class PlayerBar;
class PlaylistView;
class LibraryView;
class ComposerView;
enum class Section;

class MainWindow : public QMainWindow {
    Q_OBJECT

    Playlist *openedFiles;
    QMap<Composer *, ComposerView *> composerViewMap;

    QVBoxLayout *mainLayout;
    MenuBar *menuBar;
    SideBar *sideBar;
    PlayerBar *playerBar;
    PlaylistView *playlistView;

    PlaylistView *filesView;
    LibraryView *libView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MenuBar *getMenuBar() const;
    SideBar *getSideBar() const;
    PlayerBar *getPlayerBar() const;
    PlaylistView *getPlaylistView() const;
    void setPlaylistView(Section section);
    void setComposerView(Composer *composer);

    void openFiles();
    void setSideBarVisible(bool visible);
};
