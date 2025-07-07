#include "AppData.h"

#include "Library.h"
#include "Piece.h"
#include "Playback.h"

#include <QApplication>
#include <QDataStream>
#include <QFile>

AppData::AppData() :
    lib{new Library},
    repeat{Repeat::Off},
    volume{Volume::DefaultVolume} {}

AppData::~AppData() {
    delete lib;
}

Library *AppData::getLibrary() const {
    return lib;
}

void AppData::setRepeat(Repeat repeat) {
    this->repeat = repeat;
}

Repeat AppData::getRepeat() const {
    return repeat;
}

void AppData::setVolume(int volume) {
    Q_ASSERT(Volume::MinVolume <= volume && volume <= Volume::MaxVolume);
    this->volume = volume;
}

int AppData::getVolume() const {
    return volume;
}

void AppData::save() const {
    QFile file{appDataFilePath()};
    if (!file.open(QFile::WriteOnly)) return;

    QDataStream out{&file};
    const int numPieces{lib->size()};
    out << numPieces;
    for (auto piece : lib->getPieces()) {
        out << piece->getId()
            << piece->getName()
            << piece->getSource()
            << piece->getComposer()
            << piece->getPlayCount();
    }
    out << repeat;
    out << volume;
}

bool AppData::load() {
    QFile file{appDataFilePath()};
    if (!file.open(QFile::ReadOnly)) return false;

    QDataStream in{&file};
    int numPieces{0};
    in >> numPieces;

    for (int i = 0; i < numPieces; ++i) {
        QUuid id;
        QString name;
        QUrl source;
        QString composer;
        int playCount{0};
        in >> id >> name >> source >> composer >> playCount;

        const auto piece = new Piece{source, name, composer};
        piece->setId(id);
        piece->setPlayCount(playCount);
        lib->addPiece(piece);
    }

    in >> repeat;
    in >> volume;
    return true;
}

QString AppData::appDataFilePath() {
    return QApplication::applicationDirPath() + "/QClassic_Data";
}

AppData &AppData::instance() {
    static AppData data;
    return data;
}
