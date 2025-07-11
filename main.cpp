#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_WAYLAND_FORCE_WINDOW_CLASS", "rznzTuner");

    QApplication a(argc, argv);
    a.setApplicationDisplayName("roazanas tuner");
    MainWindow w;
    w.setWindowTitle("roazanas tuner");
    w.show();
    return a.exec();
}
