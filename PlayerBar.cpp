#include "PlayerBar.h"
#include "MainWindow.h"
#include "MenuBar.h"
#include "TreeView.h"
#include "Composition.h"

#include <QHBoxLayout>
#include <QTime>

static const int MAX_VOLUME{100};

PlayerBar::PlayerBar(MainWindow *win) : QFrame{win}, win{win},
    playButton{new QPushButton{"Play", this}},
    prevButton{new QPushButton{"Prev", this}},
    nextButton{new QPushButton{"Next", this}},
    timeSlider{new QSlider{Qt::Horizontal, this}},
    timeLabel{new QLabel{QTime::fromMSecsSinceStartOfDay(0).toString(), this}},
    volumeSlider{new QSlider{Qt::Horizontal, this}},
    volumeLabel{new QLabel{QString::number(MAX_VOLUME) + "%", this}}, volume{MAX_VOLUME},
    currComposition{nullptr}, playing{false} {

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

    connect(volumeSlider, &QSlider::valueChanged, this, [this] (int val) {
        volume = val;
        currComposition->getMediaPlayer()->audioOutput()->setVolume(1.0 * volume / MAX_VOLUME);
        volumeLabel->setText(QString::number(val) + "%");
    });

    connect(playButton, &QPushButton::clicked, this, &PlayerBar::playOrPause);
    connect(prevButton, &QPushButton::clicked, this,
            [win] { win->getTreeView()->selectPrev(); });
    connect(nextButton, &QPushButton::clicked, this,
            [win] { win->getTreeView()->selectNext(); });

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
    win->setWindowTitle(composition ? composition->getTitle() : "");

    if (!composition) return;

    timeSlider->setValue(0);
    timeSlider->setMaximum(composition->getDurationMs());
    timeLabel->setText(QTime::fromMSecsSinceStartOfDay(0).toString());

    composition->getMediaPlayer()->audioOutput()->setVolume(1.0 * volume / MAX_VOLUME);

    auto player = currComposition->getMediaPlayer();
    connect(player, &QMediaPlayer::positionChanged, this, [this] (int pos) {
        if (timeSlider->isSliderDown()) return;

        timeSlider->setValue(pos);
        timeLabel->setText(QTime::fromMSecsSinceStartOfDay(pos).toString());
    });

    play();
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
