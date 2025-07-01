#include "Composition.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTime>

QString Composition::millisecToString(int ms) {
    return QTime::fromMSecsSinceStartOfDay(ms).toString();
}

Composition::Composition(const QUrl &source, const QString &name,
                         const QString &composer, const QUuid &id) :
    LibraryItem{name.isEmpty() ? source.fileName() : name, nullptr, id},
    source{source}, composer{composer},
    player{new QMediaPlayer}, audioOutput{new QAudioOutput} {

    player->setSource(source);
    player->setAudioOutput(audioOutput);
}

Composition::~Composition() {
    delete audioOutput;
    delete player;
}

QUrl Composition::getSource() const {
    return source;
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

bool Composition::operator==(const Composition &other) {
    return (getName() == other.getName()) &&
           (getComposer() == other.getComposer() &&
           (getDurationMs() == other.getDurationMs()) &&
           (getSource() == other.getSource()));
}
