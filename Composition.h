#pragma once

#include <QString>
#include <QUrl>
#include <QMediaPlayer>

class Composer;

class Composition {
    QUrl source;
    QString title;
    Composer *composer;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;

public:
    Composition(const QUrl &source, const QString &title = "",
                Composer *composer = nullptr);
    ~Composition();

    void setTitle(const QString &title);
    QString getTitle() const;

    void setComposer(Composer *composer);
    Composer *getComposer() const;

    QMediaPlayer *getMediaPlayer() const;
    int getDurationMs() const;
    QString getDurationFormat() const;
};
