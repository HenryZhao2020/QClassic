#include "PlayerBar.h"
#include "MainWindow.h"
#include "IPieceView.h"
#include "Piece.h"
#include "AppData.h"
#include "Playback.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>

PlayerBar::PlayerBar(MainWindow *win) : QFrame{win}, win{win},
    playButton{new QPushButton{"Play", this}},
    prevButton{new QPushButton{"Prev", this}},
    nextButton{new QPushButton{"Next", this}},
    timeSlider{new QSlider{Qt::Horizontal, this}},
    timeLabel{new QLabel{Piece::millisecToString(0), this}},
    volumeSlider{new QSlider{Qt::Horizontal, this}},
    volumeLabel{new QLabel{this}},
    currPiece{nullptr}, playing{false} {

    auto barLayout = new QHBoxLayout{this};
    barLayout->setAlignment(Qt::AlignLeft);
    barLayout->setSpacing(0);
    barLayout->addWidget(prevButton);
    barLayout->addWidget(playButton);
    barLayout->addWidget(nextButton);
    barLayout->addWidget(timeSlider, 1);
    barLayout->addWidget(timeLabel);
    barLayout->addWidget(volumeSlider);
    barLayout->addWidget(volumeLabel);

    connect(timeSlider, &QSlider::sliderReleased, this, [this] {
        currPiece->getMediaPlayer()->setPosition(timeSlider->value());
    });

    const int volume{AppData::instance().getVolume()};
    volumeLabel->setText(QString{"%1%"}.arg(volume));
    volumeSlider->setMinimum(Volume::MinVolume);
    volumeSlider->setMaximum(Volume::MaxVolume);
    volumeSlider->setValue(volume);
    connect(volumeSlider, &QSlider::valueChanged, this,
            &PlayerBar::updateVolumeSlider);

    connect(playButton, &QPushButton::clicked, this,
            &PlayerBar::playOrPause);
    connect(prevButton, &QPushButton::clicked, this, [win] {
        win->getPieceView()->selectPrev();
    });
    connect(nextButton, &QPushButton::clicked, this, [win] {
        win->getPieceView()->selectNext();
    });

    setEnabled(false);
}

void PlayerBar::setCurrentPiece(Piece *piece) {
    if (currPiece) {
        currPiece->getMediaPlayer()->stop();
    }
    currPiece = piece;

    setEnabled(piece);
    win->setWindowTitle(piece ? piece->getName() : "");
    initTimeSlider(piece);

    if (!piece) return;

    piece->setVolume(AppData::instance().getVolume());
    win->getPieceView()->increasePlayCount(piece);
    connect(currPiece->getMediaPlayer(), &QMediaPlayer::positionChanged,
            this, &PlayerBar::updateTimeSlider);
    play();
}

Piece *PlayerBar::getCurrentPiece() const {
    return currPiece;
}

void PlayerBar::updateDuration() {
    if (currPiece) {
        timeSlider->setMaximum(currPiece->getDurationMs());
    }
}

void PlayerBar::playOrPause() {
    if (playing) pause();
    else play();
}

void PlayerBar::play() {
    Q_ASSERT(currPiece);

    currPiece->getMediaPlayer()->play();
    playButton->setText("Pause");
    playing = true;
}

void PlayerBar::pause() {
    Q_ASSERT(currPiece);

    currPiece->getMediaPlayer()->pause();
    playButton->setText("Play");
    playing = false;
}

void PlayerBar::initTimeSlider(Piece *piece) {
    timeSlider->setValue(0);
    timeLabel->setText(Piece::millisecToString(0));

    if (piece) {
        timeSlider->setMaximum(piece->getDurationMs());
    }
}

void PlayerBar::updateTimeSlider(int ms) {
    if (timeSlider->isSliderDown()) return;

    if (ms == currPiece->getDurationMs()) {
        win->getPieceView()->selectNext();
    } else {
        timeSlider->setValue(ms);
        timeLabel->setText(Piece::millisecToString(ms));
    }
}

void PlayerBar::updateVolumeSlider(int volume) {
    AppData::instance().setVolume(volume);
    currPiece->setVolume(volume);
    volumeLabel->setText(QString{"%0%"}.arg(volume));
}
