#pragma once

#include "LibraryItem.h"

#include <QUrl>
#include <QString>

class Composer;
class QMediaPlayer;
class QAudioOutput;

class Composition : public LibraryItem {
    QUrl source;
    Composer *composer;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

public:
    static QString millisecToString(int ms);

    Composition(const QUrl &source, const QString &name = "",
                Composer *composer = nullptr);
    ~Composition();

    void setComposer(Composer *composer);
    Composer *getComposer() const;

    QMediaPlayer *getMediaPlayer() const;
    int getDurationMs() const;
    QString getDurationString() const;
};
