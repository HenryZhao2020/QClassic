#include "Piece.h"

#include "Playback.h"

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QTime>

QString Piece::millisecToString(int ms) {
    return QTime::fromMSecsSinceStartOfDay(ms).toString();
}

Piece::Piece(const QUrl &source, const QString &name,
             const QString &composer) :
    Identifiable{name.isEmpty() ? source.fileName() : name},
    source{source}, composer{composer}, player{new QMediaPlayer} {

    player->setSource(source);
    player->setAudioOutput(new QAudioOutput{player});
}

Piece::~Piece() {
    delete player;
}

QUrl Piece::getSource() const {
    return source;
}

void Piece::setComposer(const QString &composer) {
    this->composer = composer;
}

QString Piece::getComposer() const {
    return composer;
}

void Piece::setPlayCount(int playCount) {
    this->playCount = playCount;
}

int Piece::getPlayCount() const {
    return playCount;
}

QMediaPlayer *Piece::getMediaPlayer() const {
    return player;
}

void Piece::setVolume(int volume) {
    player->audioOutput()->setVolume(Volume::volumeAsDecimal(volume));
}

int Piece::getDurationMs() const {
    return player->duration();
}

QString Piece::getDurationString() const {
    return millisecToString(getDurationMs());
}

bool Piece::operator==(const Piece &other) {
    return (getSource() == other.getSource());
}
