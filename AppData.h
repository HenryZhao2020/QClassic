#pragma once

#include <QString>

class Library;

enum class Repeat { Off, All, One };

class AppData {
    Library *lib;
    Repeat repeat;
    bool sideBarVisible;

    static QString appDataFilePath();

    AppData();

public:
    static AppData &instance();

    ~AppData();

    Library *getLibrary() const;

    void setRepeat(Repeat repeat);
    Repeat getRepeat() const;

    void setSideBarVisible(bool visible);
    bool isSideBarVisible() const;

    void save();
    bool load();
};
