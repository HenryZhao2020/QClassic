#pragma once

enum class Repeat { Off, All, One };

class AppData {
    Repeat repeat;

    AppData();

public:
    static AppData &instance();

    void setRepeat(Repeat repeat);
    Repeat getRepeat() const;
};
