#include "audioconfig.h"

AudioConfig::AudioConfig(QObject *parent)
    : QObject{parent}
{
    for (auto &deviceInfo : QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        cpplistDevices.append(deviceInfo);
        listDevicesName.append(deviceInfo.deviceName());
        // qDebug() << deviceInfo.deviceName();
    }

    changeDevice(0);
    m_deviceInfo = QAudioDeviceInfo::defaultInputDevice();

    m_settings.setSampleRate(8000);
    m_settings.setChannelCount(1);
    m_settings.setSampleSize(16);
    m_settings.setSampleType(QAudioFormat::SignedInt);
    m_settings.setByteOrder(QAudioFormat::LittleEndian);
    m_settings.setCodec("audio/pcm");

    if (!m_deviceInfo.isFormatSupported(m_settings)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_settings = m_deviceInfo.nearestFormat(m_settings);
    }
    // m_settings.setSampleRate(m_deviceInfo.supportedSampleRates().at(0));
    // m_settings.setChannelCount(m_deviceInfo.supportedChannelCounts().at(0));
    // m_settings.setCodec(m_deviceInfo.supportedCodecs().at(0));
    // m_settings.setByteOrder(m_deviceInfo.supportedByteOrders().at(0));
    // m_settings.setSampleType(m_deviceInfo.supportedSampleTypes().at(0));
    // m_settings.setSampleSize(m_deviceInfo.supportedSampleSizes().at(0));
}

void AudioConfig::changeDevice(int idx)
{
    if (cpplistDevices.empty())
        qWarning() << "no device found";

    m_deviceInfo = cpplistDevices[idx];

    setListSampleRate(m_deviceInfo.supportedSampleRates());
    if (m_deviceInfo.supportedSampleRates().size())
        m_settings.setSampleRate(m_deviceInfo.supportedSampleRates().at(0));

    setListChannel(m_deviceInfo.supportedChannelCounts());
    if (m_deviceInfo.supportedChannelCounts().size())
        m_settings.setChannelCount(m_deviceInfo.supportedChannelCounts().at(0));

    setListCodecs(m_deviceInfo.supportedCodecs());
    if (m_deviceInfo.supportedCodecs().size())
        m_settings.setCodec(m_deviceInfo.supportedCodecs().at(0));

    setListEndianz(m_deviceInfo.supportedByteOrders());
    if (m_deviceInfo.supportedByteOrders().size())
        m_settings.setByteOrder(m_deviceInfo.supportedByteOrders().at(0));
}

QStringList AudioConfig::listDevices() const
{
    return listDevicesName;
}
void AudioConfig::setListDevices(const QStringList &newListDevices)
{
    if (m_listDevices == newListDevices)
        return;
    m_listDevices = newListDevices;
    emit listDevicesChanged();
}

QList<int> AudioConfig::listSampleRate() const
{
    return m_listSampleRate;
}
void AudioConfig::setListSampleRate(const QList<int> &newListSampleRate)
{
    if (m_listSampleRate == newListSampleRate)
        return;
    m_listSampleRate = newListSampleRate;
    // qDebug()<<"sampRate"<<m_listSampleRate;
    emit listSampleRateChanged();
}

QList<int> AudioConfig::listChannel() const
{
    return m_listChannel;
}
void AudioConfig::setListChannel(const QList<int> &newListChannel)
{
    if (m_listChannel == newListChannel)
        return;
    m_listChannel = newListChannel;
    emit listChannelChanged();
}

QStringList AudioConfig::listCodecs() const
{
    return m_listCodecs;
}
void AudioConfig::setListCodecs(const QStringList &newListCodecs)
{
    if (m_listCodecs == newListCodecs)
        return;
    m_listCodecs = newListCodecs;
    emit listCodecsChanged();
}

QList<QAudioFormat::Endian> AudioConfig::listEndianz() const
{
    return m_listEndianz;
}

void AudioConfig::setListEndianz(const QList<QAudioFormat::Endian> &newListEndianz)
{
    if (m_listEndianz == newListEndianz)
        return;
    m_listEndianz = newListEndianz;
    emit listEndianzChanged();
}

void AudioConfig::saveConfig(int device, int codec, int sampleRate, int channel, int endian)
{
    if (codec == -1) {
        qWarning() << "Codec index out of range, using default codec.";
        // m_settings.setCodec("");
    } else {
        m_settings.setCodec(listCodecs().at(codec));
    }

    // int checkVar = 0;
    m_deviceInfo = cpplistDevices[device];
    m_settings.setSampleRate(listSampleRate().at(sampleRate));
    m_settings.setChannelCount(listChannel().at(channel));
    m_settings.setByteOrder(listEndianz().at(endian));

    m_settings.setSampleSize(16);
    m_settings.setSampleType(QAudioFormat::SignedInt);

    if (!m_deviceInfo.isFormatSupported(m_settings)) {
        qWarning() << "Default format not supported";
        // m_settings = m_deviceInfo.nearestFormat(m_settings);
        // checkVar = 1;
    }

    m_nearistParams.clear();

    m_nearistParams.append(device);
    m_nearistParams.append(codec);
    m_nearistParams.append(sampleRate);
    m_nearistParams.append(channel);
    m_nearistParams.append(endian);
    // m_nearistParams.append(checkVar);

    qInfo()<< "save params: " << m_nearistParams;
}

QAudioDeviceInfo AudioConfig::deviceInfo() const
{
    return m_deviceInfo;
}

QAudioFormat AudioConfig::settings() const
{
    return m_settings;
}

QList<int> AudioConfig::nearistParams() const
{
    return m_nearistParams;
}

