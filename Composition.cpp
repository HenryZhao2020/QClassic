#include "Composition.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTime>

QString Composition::millisecToString(int ms) {
    return QTime::fromMSecsSinceStartOfDay(ms).toString();
}

Composition::Composition(const QUrl &source, const QString &name,
                         const QString &composer) :
    LibraryItem{name.isEmpty() ? source.fileName() : name},
    source{source}, composer{composer},
    player{new QMediaPlayer}, audioOutput{new QAudioOutput} {

    player->setSource(source);
    player->setAudioOutput(audioOutput);
}

Composition::~Composition() {
    delete audioOutput;
    delete player;
}

void Composition::setComposer(const QString &composer) {
    this->composer = composer;
}

QString Composition::getComposer() const {
    return composer;
}

QMediaPlayer *Composition::getMediaPlayer() const {
    return player;
}

int Composition::getDurationMs() const {
    return player->duration();
}

QString Composition::getDurationString() const {
    return millisecToString(getDurationMs());
}
