#pragma once

#include "Identifiable.h"

#include <QString>
#include <QUrl>

class QMediaPlayer;

class Piece : public Identifiable {
    QUrl source;
    QString composer;
    int playCount;
    QMediaPlayer *player;

public:
    static QString millisecToString(int ms);

    Piece(const QUrl &source, const QString &name = "",
          const QString &composer = "");
    ~Piece();

    QUrl getSource() const;

    void setComposer(const QString &composer);
    QString getComposer() const;

    void setPlayCount(int playCount);
    int getPlayCount() const;

    QMediaPlayer *getMediaPlayer() const;
    void setVolume(int volume);
    int getDurationMs() const;
    QString getDurationString() const;

    bool operator==(const Piece &other);
};
