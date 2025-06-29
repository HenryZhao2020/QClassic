#pragma once

class Library;

enum class Repeat { Off, All, One };

class AppData {
    Library *lib;
    Repeat repeat;
    bool sideBarVisible;

    AppData();

public:
    ~AppData();

    static AppData &instance();

    Library *getLibrary() const;    
    void setRepeat(Repeat repeat);
    Repeat getRepeat() const;
    void setSideBarVisible(bool visible);
    bool isSideBarVisible() const;
};
