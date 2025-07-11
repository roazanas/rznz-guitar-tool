#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>

#include <rtaudio/RtAudio.h>
#include "devicechooser.h"
#include "audioprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RtAudio *audio;

    DeviceChooser *deviceChooser;
    AudioProcessor *audioProcessor;

    unsigned int inputDeviceId;
    unsigned int outputDeviceId;

private slots:
    void onDevicesChanged(int inId, int outId);
    void on_actionSelect_devices_triggered();
};
#endif // MAINWINDOW_H
