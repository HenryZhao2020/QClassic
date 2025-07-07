#pragma once

#include <QMenuBar>

class MainWindow;
class QActionGroup;

enum class Repeat;

class MenuBar : public QMenuBar {
    Q_OBJECT

    MainWindow *win;

    QMenu *repeatMenu;
    QActionGroup *repeatGroup;

    void makeFileMenu();
    void makeEditMenu();
    void makeViewMenu();
    void makeCtrlMenu();

    void addRepeatMode(const QString &text, Repeat repeat);

public:
    MenuBar(MainWindow *win);
};
