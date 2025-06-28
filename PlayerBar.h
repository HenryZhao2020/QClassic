#pragma once

#include <QFrame>
#include <QPushButton>
#include <QLabel>

class MainWindow;
class Composition;

class PlayerBar : public QFrame {
    Q_OBJECT

    MainWindow *win;
    QPushButton *prevButton;
    QPushButton *playButton;
    QPushButton *nextButton;
    Composition *currComposition;
    bool playing;

public:
    PlayerBar(MainWindow *win);

    void setCurrentComposition(Composition *composition);
    void play();
    void pause();
};
