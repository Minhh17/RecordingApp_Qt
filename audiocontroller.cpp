    #include "audiocontroller.h"
#include <QDebug>

AudioController::AudioController(AudioConfig *config, QObject *parent)
    : QObject{parent}, m_audioIO(new AudioIO(this)), m_outputFile(new QFile()), m_audioConfig(config)
{
    connect(m_audioIO, &AudioIO::sendData, this, &AudioController::handleDataReady);
    qDebug() << "Address of m_audioConfig in AudioController:" << m_audioConfig;

    m_outputFile.setFileName("/home/haiminh/Desktop/MinhTestESCA3/dataNe/minh.wav");
    setRecStatus(false);

}

void AudioController::startRecord()
{
    qInfo()<<m_audioConfig->settings().channelCount();
    qInfo()<<m_audioConfig->deviceInfo().deviceName();

    QAudioFormat format = m_audioConfig->settings();
    QAudioDeviceInfo deviceInfo = m_audioConfig->deviceInfo();

    qInfo()<<"start controller";

    // m_audioDevice->start();
    m_audioIO->start(format, deviceInfo);
    setRecStatus(true);
}

void AudioController::pauseRecord()
{

}

void AudioController::stopRecord()
{
    m_audioIO->stop();
    qDebug()<< "stop rec";
    setRecStatus(false);
}

void AudioController::handleDataReady(const QByteArray &data)
{
    if (m_outputFile.isOpen()) {
        m_outputFile.write(data);
    }
    // qInfo() << "Data Controller: " << data;
}

bool AudioController::recStatus() const
{
    return m_recStatus;
}

void AudioController::setRecStatus(bool newRecStatus)
{
    if (m_recStatus == newRecStatus)
        return;
    m_recStatus = newRecStatus;
    emit recStatusChanged();
}
