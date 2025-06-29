#include "Composition.h"
#include "Composer.h"

#include <QTime>

QString Composition::millisecToString(int ms) {
    return QTime::fromMSecsSinceStartOfDay(ms).toString();
}

Composition::Composition(const QUrl &source, const QString &title,
                         Composer *composer)
    : source{source}, title{title.isEmpty() ? source.fileName() : title},
      composer{composer}, player{new QMediaPlayer},
      audioOutput{new QAudioOutput} {

    player->setSource(source);
    player->setAudioOutput(audioOutput);
}

Composition::~Composition() {
    delete audioOutput;
    delete player;
}

void Composition::setTitle(const QString &title) {
    this->title = title;
}

QString Composition::getTitle() const {
    return title;
}

void Composition::setComposer(Composer *composer) {
    this->composer = composer;
}

Composer *Composition::getComposer() const {
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
