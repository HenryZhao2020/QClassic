#include "Library.h"

Music::Music(const QString &title, Composer *composer, Genre *genre,
    Playlist *playlist, const QString &filePath) : title{title}, composer{composer},
    genre{genre}, playlist{playlist}, filePath{filePath} {}

void Music::setTitle(const QString &title) { this->title = title; }
QString Music::getTitle() const { return title; }

void Music::setComposer(Composer *composer) { this->composer = composer; }
Composer *Music::getComposer() const { return composer; }

void Music::setGenre(Genre *genre) { this->genre = genre; }
Genre *Music::getGenre() const { return genre; }

void Music::setPlaylist(Playlist *playlist) { this->playlist = playlist; }
Playlist *Music::getPlaylist() const { return playlist; }

void Music::setFilePath(const QString &filePath) { this->filePath = filePath; }
QString Music::getFilePath() const { return filePath; }

Composer::Composer(const QString &name) : name{name} {}

void MusicGroup::setName(const QString &name) { this->name = name; }
QString MusicGroup::getName() const { return name; }

void MusicGroup::addMusic(Music *music) { musics.append(music); }
void MusicGroup::removeMusic(Music *music) { musics.removeOne(music); }

QString Composer::getLastName() const {
    return name.mid(name.lastIndexOf(" ") + 1);
}

Library &Library::instance() {
    static Library instance;
    return instance;
}

Library::Library() {}

Library::~Library() {
    for (auto music : std::as_const(musics)) delete music;
    for (auto composer : std::as_const(composers)) delete composer;
    for (auto genre : std::as_const(genres)) delete genre;
    for (auto playlist : std::as_const(playlists)) delete playlist;
}

void Library::addMusic(Music *music) {
    Q_ASSERT(music);
    musics.append(music);
}

void Library::addComposer(Composer *composer) {
    Q_ASSERT(composer);
    composers.append(composer);
}

void Library::addGenre(Genre *genre) {
    Q_ASSERT(genre);
    genres.append(genre);
}

void Library::addPlaylist(Playlist *playlist) {
    Q_ASSERT(playlist);
    playlists.append(playlist);
}

Music *Library::findMusic(const QString &title, const QString &composerName) const {
    for (auto music : std::as_const(musics)) {
        if (music->getTitle() == title &&
            music->getComposer()->getName() == composerName) {
            return music;
        }
    }
    return nullptr;
}

Composer *Library::findComposer(const QString &name) const {
    for (auto composer : std::as_const(composers)) {
        if (composer->getName() == name) {
            return composer;
        }
    }
    return nullptr;
}

Genre *Library::findGenre(const QString &name) const {
    for (auto genre : std::as_const(genres)) {
        if (genre->getName() == name) {
            return genre;
        }
    }
    return nullptr;
}

Playlist *Library::findPlaylist(const QString &name) const {
    for (auto playlist : std::as_const(playlists)) {
        if (playlist->getName() == name) {
            return playlist;
        }
    }
    return nullptr;
}

const QList<Composer *> Library::getComposers() const { return composers; }
const QList<Genre *> Library::getGenres() const { return genres; }
const QList<Playlist *> Library::getPlaylists() const { return playlists; }
