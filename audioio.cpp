#include "audioio.h"
#include <QDebug>

AudioIO::AudioIO(QObject *parent)
    : QObject(parent),
    m_audioInput(nullptr), m_audioIODevice2(nullptr)
{

}

AudioIO::~AudioIO() {
    stop();
}

void AudioIO::start(const QAudioFormat& format, const QAudioDeviceInfo& deviceInfo) {

    if (m_audioInput) delete m_audioInput;
    m_audioInput = nullptr;

    qInfo()<<"start initial ";

    m_audioInput = new QAudioInput(deviceInfo, format, this);
    // m_audioIODevice = m_audioInput->start();
    m_audioIODevice2 = m_audioInput->start();

    if(m_audioIODevice2 == nullptr) qDebug()<<"nullptr QIODEv";

    connect(m_audioIODevice2, &QIODevice::readyRead, this, &AudioIO::onReadyRead);
}

void AudioIO::stop() {
    stop();
    delete m_audioInput;
    m_audioInput = nullptr;
}

void AudioIO::onReadyRead()
{
    if (m_audioInput && m_audioIODevice) {
        qDebug()<< "here is handleDatainput";
        QByteArray data = m_audioIODevice2->readAll();
        emit sendData(data);
        // qInfo()<<"dataNE"<<data;
    }
}

