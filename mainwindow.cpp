#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    audio = new RtAudio(RtAudio::Api::UNIX_JACK);

    deviceChooser = new DeviceChooser(this, audio);
    deviceChooser->setAttribute(Qt::WA_DeleteOnClose, false);

    connect(
        deviceChooser,
        &DeviceChooser::devicesChanged,
        this,
        &MainWindow::onDevicesChanged
    );

    deviceChooser->setDefaults();

    inputDeviceId = deviceChooser->inputDeviceId;
    outputDeviceId = deviceChooser->outputDeviceId;

    audioProcessor = new AudioProcessor(audio, inputDeviceId, outputDeviceId);
    audioProcessor->start();
}

MainWindow::~MainWindow()
{
    delete audioProcessor;
    delete ui;
}

void MainWindow::on_actionSelect_devices_triggered()
{
    deviceChooser->exec();
}

void MainWindow::onDevicesChanged(int inId, int outId)
{
    audioProcessor->setDevices(inId, outId);
}
