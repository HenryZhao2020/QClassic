#include "MainWindow.h"
#include "SideBar.h"
#include "AppData.h"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    QDir::setCurrent(QStandardPaths::writableLocation(
        QStandardPaths::MusicLocation));

    QApplication::connect(&app, &QApplication::aboutToQuit, &app,
                          [] { AppData::instance().save(); });

    QFile styleSheet{":/conf/Styles.qss"};
    if (styleSheet.open(QFile::ReadOnly)) {
        app.setStyleSheet(styleSheet.readAll());
    }
    styleSheet.close();

    AppData::instance().load();

    MainWindow win;
    win.show();
    return app.exec();
}
