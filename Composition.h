#pragma once

#include "Identifiable.h"

#include <QUrl>
#include <QString>
#include <QUuid>

class QMediaPlayer;
class QAudioOutput;

class Composition : public Identifiable {
    QUrl source;
    QString composer;
    int playCount;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

public:
    static QString millisecToString(int ms);

    Composition(const QUrl &source, const QString &name = "",
                const QString &composer = "");
    ~Composition();

    QUrl getSource() const;

    void setComposer(const QString &composer);
    QString getComposer() const;

    void setPlayCount(int playCount);
    int getPlayCount() const;

    QMediaPlayer *getMediaPlayer() const;

    int getDurationMs() const;
    QString getDurationString() const;

    bool operator==(const Composition &other);
};
