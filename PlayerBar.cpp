#include "PlayerBar.h"
#include "MainWindow.h"
#include "TreeView.h"
#include "Composition.h"

#include <QHBoxLayout>

PlayerBar::PlayerBar(MainWindow *win) : QFrame{win}, win{win},
    prevButton{new QPushButton{"Prev", this}},
    playButton{new QPushButton{"Play", this}},
    nextButton{new QPushButton{"Next", this}},
    currComposition{nullptr}, playing{false} {

    auto barLayout = new QHBoxLayout{this};
    barLayout->setAlignment(Qt::AlignCenter);
    barLayout->addWidget(prevButton);
    barLayout->addWidget(playButton);
    barLayout->addWidget(nextButton);

    connect(playButton, &QPushButton::clicked, this, [this] {
        if (playing) pause();
        else play();
    });

    connect(prevButton, &QPushButton::clicked, this, [win] {
        win->getMainView()->selectPrev();
    });

    connect(nextButton, &QPushButton::clicked, this, [win] {
        win->getMainView()->selectNext();
    });

    setEnabled(false);
}

void PlayerBar::setCurrentComposition(Composition *composition) {
    if (currComposition) {
        currComposition->getMediaPlayer()->stop();
    }
    currComposition = composition;

    setEnabled(composition);
    win->setWindowTitle(composition ? composition->getTitle() : "");
    if (composition) play();
}

void PlayerBar::play() {
    Q_ASSERT(currComposition);

    currComposition->getMediaPlayer()->play();
    playButton->setText("Pause");
    playing = true;
}

void PlayerBar::pause() {
    Q_ASSERT(currComposition);

    currComposition->getMediaPlayer()->pause();
    playButton->setText("Play");
    playing = false;
}
