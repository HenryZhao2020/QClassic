#include "Composition.h"
#include "Composer.h"

#include <QFileInfo>
#include <QTime>
#include <QMediaPlayer>
#include <QAudioOutput>

Composition::Composition(const QUrl &source, const QString &title, Composer *composer)
    : source{source},
      title{title.isEmpty() ? source.fileName() : title},
      composer{composer}, player{new QMediaPlayer}, audioOutput{new QAudioOutput} {

    player->setAudioOutput(audioOutput);
    player->setSource(source);
}

Composition::~Composition() {
    delete player;
    delete audioOutput;
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

QString Composition::getDurationFormat() const {
    QTime time = QTime::fromMSecsSinceStartOfDay(getDurationMs());
    return time.toString();
}
