#pragma once

#include "LibraryItem.h"

#include <QUrl>
#include <QString>

class QMediaPlayer;
class QAudioOutput;

class Composition : public LibraryItem {
    QUrl source;
    QString composer;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

public:
    static QString millisecToString(int ms);

    Composition(const QUrl &source, const QString &name = "",
                const QString &composer = "");
    ~Composition();

    void setComposer(const QString &composer);
    QString getComposer() const;

    QMediaPlayer *getMediaPlayer() const;
    int getDurationMs() const;
    QString getDurationString() const;
};
