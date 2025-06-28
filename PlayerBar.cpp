#include "PlayerBar.h"
#include "MainWindow.h"

#include <QHBoxLayout>
#include <QPushButton>

PlayerBar::PlayerBar(MainWindow *win) : QFrame{win} {
    auto barLayout = new QHBoxLayout{this};
    barLayout->setAlignment(Qt::AlignCenter);

    auto playButton = new QPushButton{"Play", this};
    barLayout->addWidget(playButton);
}
