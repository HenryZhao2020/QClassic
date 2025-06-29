#include "PlayerBar.h"
#include "MainWindow.h"
#include "MenuBar.h"
#include "PlaylistView.h"
#include "Composition.h"

#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QAudioOutput>

static constexpr int MAX_VOLUME{100};

PlayerBar::PlayerBar(MainWindow *win) : QFrame{win}, win{win},
    playButton{new QPushButton{"Play", this}},
    prevButton{new QPushButton{"Prev", this}},
    nextButton{new QPushButton{"Next", this}},
    timeSlider{new QSlider{Qt::Horizontal, this}},
    timeLabel{new QLabel{Composition::millisecToString(0), this}},
    volumeSlider{new QSlider{Qt::Horizontal, this}},
    volumeLabel{new QLabel{QString::number(MAX_VOLUME) + "%", this}},
    volume{MAX_VOLUME}, currComposition{nullptr}, playing{false} {

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
        currComposition->getMediaPlayer()->setPosition(timeSlider->value());
    });

    volumeSlider->setMaximum(MAX_VOLUME);
    volumeSlider->setValue(MAX_VOLUME);
    connect(volumeSlider, &QSlider::valueChanged, this, [this] (int vol) {
        volume = vol;
        currComposition->getMediaPlayer()->audioOutput()
            ->setVolume(1.0 * volume / MAX_VOLUME);
        volumeLabel->setText(QString::number(volume) + "%");
    });

    connect(playButton, &QPushButton::clicked, this, &PlayerBar::playOrPause);
    connect(prevButton, &QPushButton::clicked, this,
            [win] { win->getPlaylistView()->selectPrev(); });
    connect(nextButton, &QPushButton::clicked, this,
            [win] { win->getPlaylistView()->selectNext(); });

    setEnabled(false);
}

void PlayerBar::setEnabled(bool enabled) {
    QFrame::setEnabled(enabled);
    win->getMenuBar()->playAction->setEnabled(enabled);
    win->getMenuBar()->prevAction->setEnabled(enabled);
    win->getMenuBar()->nextAction->setEnabled(enabled);
}

void PlayerBar::setCurrentComposition(Composition *composition) {
    if (currComposition) {
        currComposition->getMediaPlayer()->stop();
    }
    currComposition = composition;

    setEnabled(composition);
    win->setWindowTitle(composition ? composition->getName() : "");

    initTimeSlider(composition);
    auto player = currComposition->getMediaPlayer();
    connect(player, &QMediaPlayer::positionChanged, this,
            &PlayerBar::updateTimeSlider);

    play();
}

void PlayerBar::updateDuration() {
    if (currComposition) {
        timeSlider->setMaximum(currComposition->getDurationMs());
    }
}

void PlayerBar::playOrPause() {
    if (playing) pause();
    else play();
}

void PlayerBar::play() {
    Q_ASSERT(currComposition);

    currComposition->getMediaPlayer()->play();
    playButton->setText("Pause");
    win->getMenuBar()->playAction->setText(tr("Pause"));
    playing = true;
}

void PlayerBar::pause() {
    Q_ASSERT(currComposition);

    currComposition->getMediaPlayer()->pause();
    playButton->setText("Play");
    win->getMenuBar()->playAction->setText(tr("Play"));
    playing = false;
}

void PlayerBar::initTimeSlider(Composition *composition) {
    timeSlider->setValue(0);
    timeLabel->setText(Composition::millisecToString(0));

    if (composition) {
        timeSlider->setMaximum(composition->getDurationMs());
        composition->getMediaPlayer()->audioOutput()
            ->setVolume(1.0 * volume / MAX_VOLUME);
    }
}

void PlayerBar::updateTimeSlider(int ms) {
    if (timeSlider->isSliderDown()) return;

    if (ms == currComposition->getDurationMs()) {
        win->getPlaylistView()->selectNext();
    } else {
        timeSlider->setValue(ms);
        timeLabel->setText(Composition::millisecToString(ms));
    }
}
