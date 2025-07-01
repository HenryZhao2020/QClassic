#include "AppData.h"
#include "Library.h"
#include "Composition.h"

#include <QFile>
#include <QDataStream>
#include <QApplication>

AppData::AppData() :
    lib{new Library},
    repeat{Repeat::Off},
    sideBarVisible{true} {}

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

void AppData::setSideBarVisible(bool visible) {
    sideBarVisible = visible;
}

bool AppData::isSideBarVisible() const {
    return sideBarVisible;
}

void AppData::save() {
    QFile file{appDataFilePath()};
    if (!file.open(QFile::WriteOnly)) return;

    QDataStream out{&file};
    out << lib->getCompositions().size();
    for (auto c : lib->getCompositions()) {
        out << c->getId() << c->getSource()
            << c->getName() << c->getComposer();
    }
    out << repeat;
    out << sideBarVisible;
}

bool AppData::load() {
    QFile file{appDataFilePath()};
    if (!file.open(QFile::ReadOnly)) return false;

    QDataStream in{&file};
    qsizetype numCompositions{0};
    in >> numCompositions;

    for (qsizetype i = 0; i < numCompositions; ++i) {
        QUuid id;
        QUrl source;
        QString name, composer;
        in >> id >> source >> name >> composer;
        lib->addComposition(new Composition{source, name, composer, id});
    }

    in >> repeat;
    in >> sideBarVisible;

    return true;
}

QString AppData::appDataFilePath() {
    return QApplication::applicationDirPath() + "/QClassic_Data";
}

AppData &AppData::instance() {
    static AppData data;
    return data;
}
