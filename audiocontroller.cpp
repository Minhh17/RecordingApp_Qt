#include "audiocontroller.h"
#include <QDebug>

AudioController::AudioController(AudioConfig *config, QObject *parent)
    : QObject{parent},
    m_audioIO(new AudioIO(this)),
    m_audioConfig(config),
    m_audioFile(),
    // m_audioChart(new AudioChart()),
    m_audioChart2(new AudioChart2())
{
    qmlRegisterSingletonInstance("AudioChartImport2", 1, 0, "AudioChart2", m_audioChart2);

    connect(m_audioIO, &AudioIO::sendData, this, &AudioController::handleDataReady);
    connect(this, &AudioController::sendDataChart, m_audioChart2, &AudioChart2::onSendChartData);
    qDebug() << "Address of m_audioConfig in AudioController:" << m_audioConfig;

    // m_outputFile.setFileName("/home/haiminh/Desktop/Minh TestESCA3/dataNe/minh.wav");
    setRecStatus(false);
}

AudioController::~AudioController()
{
    delete m_audioChart;
}

void AudioController::startRecord()
{
    qInfo()<<m_audioConfig->format().channelCount();
    qInfo()<<m_audioConfig->deviceInfo().deviceName();

    QAudioFormat format = m_audioConfig->format();
    QAudioDeviceInfo deviceInfo = m_audioConfig->deviceInfo();


    if (!m_audioFile.startRecording("minhne.wav", format)) {
        qDebug() << "Không thể bắt đầu ghi âm!";
    }

    m_audioIO->start(format, deviceInfo);

    qInfo()<<"start controller";
    setRecStatus(true);
}

void AudioController::pauseRecord()
{

}

void AudioController::stopRecord()
{
    m_audioFile.stopRecording();
    m_audioIO->stop();    
    qDebug()<< "stop rec";
    setRecStatus(false);
}

void AudioController::handleDataReady(const QByteArray &data)
{
    qDebug() <<"handleDataReady-audioController"<<data.at(0);
    emit sendDataChart(data);

    m_audioFile.writeAudioData(data);

    // if (m_audioChart) {
    //     m_audioChart->onUpdateChart(data);
    // }
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



