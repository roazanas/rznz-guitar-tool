#include "devicechooser.h"
#include "ui_devicechooser.h"

DeviceChooser::DeviceChooser(QWidget *parent, RtAudio *parentAudio)
    : QDialog(parent)
    , ui(new Ui::DeviceChooser)
    , audio(parentAudio)
    , requiredSampleRate(audio->getDeviceInfo(audio->getDefaultInputDevice()).preferredSampleRate)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowFlags(Qt::Tool);

    connect(
        ui->buttonBox->button(QDialogButtonBox::RestoreDefaults),
        &QPushButton::clicked,
        this,
        &DeviceChooser::setDefaults
    );


    for (int id : audio->getDeviceIds()) {
        RtAudio::DeviceInfo info = audio->getDeviceInfo(id);

        bool okInput  = (info.inputChannels  >= requiredChannels)
                       && (std::find(info.sampleRates.begin(),
                                     info.sampleRates.end(),
                                     requiredSampleRate)
                           != info.sampleRates.end());
        bool okOutput = (info.outputChannels >= requiredChannels)
                        && (std::find(info.sampleRates.begin(),
                                      info.sampleRates.end(),
                                      requiredSampleRate)
                            != info.sampleRates.end());

        if (okInput) {
            ui->inputComboBox->addItem(
                QString::fromStdString(info.name), id
            );
        }
        if (okOutput) {
            ui->outputComboBox->addItem(
                QString::fromStdString(info.name), id
            );
        }

        // qDebug() << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        // qDebug() << "Name:" << QString::fromStdString(info.name);
        // qDebug() << "Output Channels:" << info.outputChannels;
        // qDebug() << "Input Channels:" << info.inputChannels;
        // qDebug() << "Duplex Channels:" << info.duplexChannels;
        // qDebug() << "Is Default Output:" << info.isDefaultOutput;
        // qDebug() << "Is Default Input:" << info.isDefaultInput;
        // qDebug() << "Sample Rates:" << QList<int>(info.sampleRates.begin(), info.sampleRates.end());
        // qDebug() << "Preferred Sample Rate:" << info.preferredSampleRate;
        // qDebug() << "\n\n";
    }

    setDefaults();
}

DeviceChooser::~DeviceChooser()
{
    delete ui;
}

void DeviceChooser::setDevice(int id, bool isInput)
{
    QLabel *label = isInput ? ui->inIdLabel : ui->outIdLabel;
    QComboBox *combo = isInput ? ui->inputComboBox : ui->outputComboBox;

    label->setText(QString("(id=%1)").arg(id));
    int index = combo->findData(id);
    if (index != -1)
        combo->setCurrentIndex(index);
}

void DeviceChooser::setDefaults()
{
    setDevice(audio->getDefaultInputDevice(), true);
    setDevice(audio->getDefaultOutputDevice(), false);
}

void DeviceChooser::on_inputComboBox_currentIndexChanged(int index) {
    int id = ui->inputComboBox->itemData(index).toInt();
    inputDeviceId = id;
    setDevice(id, true);
    emit devicesChanged(inputDeviceId, outputDeviceId);
}

void DeviceChooser::on_outputComboBox_currentIndexChanged(int index) {
    int id = ui->outputComboBox->itemData(index).toInt();
    outputDeviceId = id;
    setDevice(id, false);
    emit devicesChanged(inputDeviceId, outputDeviceId);
}
