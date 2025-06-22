#include "MainWindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");

    QFile style{":/conf/Styles.qss"};
    style.open(QFile::ReadOnly | QFile::Text);
    app.setStyleSheet(style.readAll());
    style.close();

    MainWindow win;
    win.show();

    return app.exec();
}
