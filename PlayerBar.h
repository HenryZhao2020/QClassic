#pragma once

#include <QFrame>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QTimer>

class MainWindow;
class Composition;
enum class Repeat;

class PlayerBar : public QFrame {
    Q_OBJECT

    MainWindow *win;
    QPushButton *playButton;
    QPushButton *prevButton;
    QPushButton *nextButton;

    QSlider *timeSlider;
    QLabel *timeLabel;

    QSlider *volumeSlider;
    QLabel *volumeLabel;
    int volume;

    Composition *currComposition;
    bool playing;
    Repeat repeat;

public:
    PlayerBar(MainWindow *win);

    void setEnabled(bool enabled);
    void setCurrentComposition(Composition *composition);
    void updateDuration();
    void playOrPause();
    void play();
    void pause();
};
