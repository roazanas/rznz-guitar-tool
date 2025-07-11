#ifndef DEVICECHOOSER_H
#define DEVICECHOOSER_H

#include <QDialog>
#include <QString>
#include <QPushButton>

#include <rtaudio/RtAudio.h>

namespace Ui {
class DeviceChooser;
}

class DeviceChooser : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceChooser(QWidget *parent = nullptr, RtAudio *parentAudio = nullptr);
    ~DeviceChooser();

    unsigned inputDeviceId = -1;
    unsigned outputDeviceId = -1;

    void setDefaults();

private slots:
    void on_outputComboBox_currentIndexChanged(int index);

    void on_inputComboBox_currentIndexChanged(int index);

private:
    Ui::DeviceChooser *ui;
    QMap<int, RtAudio::DeviceInfo> devices;
    RtAudio *audio = nullptr;

    void setDevice(int id, bool isInput);

    unsigned requiredChannels = 2;
    double requiredSampleRate;

signals:
    void devicesChanged(int inputDeviceId, int outputDeviceId);
};

#endif // DEVICECHOOSER_H
