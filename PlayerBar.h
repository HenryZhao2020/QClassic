#pragma once

#include <QFrame>

class MainWindow;
class QPushButton;
class QSlider;
class QLabel;
class Piece;

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

    Piece *currPiece;
    bool playing;

    void initTimeSlider(Piece *piece);
    void updateTimeSlider(int ms);

    void updateVolumeSlider(int volume);

public:
    PlayerBar(MainWindow *win);

    void setCurrentPiece(Piece *piece);
    Piece *getCurrentPiece() const;

    void updateDuration();
    void playOrPause();
    void play();
    void pause();
};
