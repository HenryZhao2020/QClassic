#pragma once

#include <QString>
#include <QList>
#include <QTime>
#include <QIcon>

class Composer;
class Genre;
class Playlist;

enum class Category {
    General = 0,
    Composer,
    Form,
    Era,
};

class Era;

class Composer {
    QString name;
    QString country;
    Era *era;

public:
    Composer(const QString &name);

    void setFullName(const QString &name);
    void getFullName() const;
    QString getLastName() const;
};

class Form {
    QString name;
    QString description;
    Era *initEra;
};

class Era {
    QString name;
    int startYear;
    int endYear;
};

class Instrument {
    QString name;
    QIcon icon;
};

class Music {
    // Elementary info
    QString title;
    Composer *composer;
    int year;
    QTime duration;

    Form *form;
    Era *era;
    QList<Instrument *> instruments;

    QString filePath;

public:
    Music(const QString &title, Composer *composer = nullptr, Genre *genre = nullptr,
          Playlist *playlist = nullptr, const QString &filePath = "");

    void setTitle(const QString &title);
    QString getTitle() const;

    void setComposer(Composer *composer);
    Composer *getComposer() const;

    void setGenre(Genre *genre);
    Genre *getGenre() const;

    void setPlaylist(Playlist *playlist);
    Playlist *getPlaylist() const;

    void setFilePath(const QString &filePath);
    QString getFilePath() const;
};

class Genre : public MusicGroup {};

class Playlist : public MusicGroup {};

class Library {
public:
    static Library &instance();

    Library();
    ~Library();

    void addMusic(Music *music);
    void addComposer(Composer *composer);
    void addGenre(Genre *genre);
    void addPlaylist(Playlist *playlist);

    Music *findMusic(const QString &title, const QString &composerName) const;
    Composer *findComposer(const QString &name) const;
    Genre *findGenre(const QString &name) const;
    Playlist *findPlaylist(const QString &name) const;

    const QList<Composer *> getComposers() const;
    const QList<Genre *> getGenres() const;
    const QList<Playlist *> getPlaylists() const;

private:
    QList<Music *> musics;
    QList<Composer *> composers;
    QList<Genre *> genres;
    QList<Playlist *> playlists;
};
