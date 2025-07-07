#pragma once

#include <QString>

class Library;

enum class Repeat;

class AppData {
    Library *lib;
    Repeat repeat;
    int volume;

    static QString appDataFilePath();

    AppData();

public:
    static AppData &instance();

    ~AppData();

    Library *getLibrary() const;

    void setRepeat(Repeat repeat);
    Repeat getRepeat() const;

    void setVolume(int volume);
    int getVolume() const;

    void save() const;
    bool load();
};
