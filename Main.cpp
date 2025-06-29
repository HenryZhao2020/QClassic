#include "MainWindow.h"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    QDir::setCurrent(QStandardPaths::writableLocation(QStandardPaths::MusicLocation));

    QFile styleSheet{":/conf/Styles.qss"};
    if (styleSheet.open(QFile::ReadOnly)) {
        app.setStyleSheet(styleSheet.readAll());
    }
    styleSheet.close();

    MainWindow win;
    win.show();
    return app.exec();
}
