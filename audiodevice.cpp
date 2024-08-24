#include "audiodevice.h"

AudioDevice::AudioDevice(const QAudioFormat &format, QObject *parent)
    : QIODevice(parent), m_format(format)
{
    switch (m_format.sampleSize()) {
    case 8:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 255;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 127;
            break;
        default:
            break;
        }
        break;
    case 16:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 65535;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 32767;
            break;
        default:
            break;
        }
        break;
    case 32:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 0xffffffff;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 0x7fffffff;
            break;
        case QAudioFormat::Float:
            m_maxAmplitude = 0x7fffffff; // assumes normalized float [-1.0, 1.0]
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void AudioDevice::start()
{
    open(QIODevice::WriteOnly);
}

void AudioDevice::stop()
{
    close();
}

qint64 AudioDevice::readData(char *data, qint64 maxlen)
{
}

qint64 AudioDevice::writeData(const char *data, qint64 len)
{

}

qreal AudioDevice::level() const
{
    return m_level;
}

