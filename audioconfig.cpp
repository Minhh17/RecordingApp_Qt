#include "audioconfig.h"

AudioConfig::AudioConfig(QObject *parent)
    : QObject{parent}
{
    m_nearistParams[0] = m_settings.value("audio/device", 0).toInt();
    m_nearistParams[1] = m_settings.value("audio/codec", 0).toInt();
    m_nearistParams[2] = m_settings.value("audio/sampleRate", 0).toInt();
    m_nearistParams[3] = m_settings.value("audio/channel", 0).toInt();
    m_nearistParams[4] = m_settings.value("audio/endian", 0).toInt();
    qInfo() << "m_nearistParams: "<<m_nearistParams;

    for (auto &deviceInfo : QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        cpplistDevices.append(deviceInfo);
        listDevicesName.append(deviceInfo.deviceName());
        // qDebug() << deviceInfo.deviceName();
    }

    m_deviceInfo = cpplistDevices[m_nearistParams[0]];
    m_format.setCodec(m_deviceInfo.supportedCodecs().at(m_nearistParams[1]));
    m_format.setSampleRate(m_deviceInfo.supportedSampleRates().at(m_nearistParams[2]));
    m_format.setChannelCount(m_deviceInfo.supportedChannelCounts().at(m_nearistParams[3]));
    m_format.setByteOrder(m_deviceInfo.supportedByteOrders().at(m_nearistParams[4]));
    m_format.setSampleSize(16);
    m_format.setSampleType(QAudioFormat::SignedInt);

    qInfo() << "m_format: "<<m_format;
    qInfo() << "1: "<< m_format.sampleRate();

    setListSampleRate(m_deviceInfo.supportedSampleRates());
    setListChannel(m_deviceInfo.supportedChannelCounts());
    setListCodecs(m_deviceInfo.supportedCodecs());
    setListEndianz(m_deviceInfo.supportedByteOrders());

    // if (!m_deviceInfo.isFormatSupported(m_format)) {
    //     qWarning() << "Default format not supported - trying to use nearest";
    //     m_format = m_deviceInfo.nearestFormat(m_format);
    // }
}

void AudioConfig::changeDevice(int idx)
{
    if (cpplistDevices.empty())
        qWarning() << "no device found";

    m_deviceInfo = cpplistDevices[idx];
    m_nearistParams[0] = idx;  // Cập nhật index thiết bị

    setListSampleRate(m_deviceInfo.supportedSampleRates());
    if (!m_deviceInfo.supportedSampleRates().empty()) {
        m_format.setSampleRate(m_deviceInfo.supportedSampleRates().at(0));
        m_nearistParams[2] = 0;  // Cập nhật index sample rate
    }

    setListChannel(m_deviceInfo.supportedChannelCounts());
    if (!m_deviceInfo.supportedChannelCounts().empty()) {
        m_format.setChannelCount(m_deviceInfo.supportedChannelCounts().at(0));
        m_nearistParams[3] = 0;  // Cập nhật index channel
    }

    setListCodecs(m_deviceInfo.supportedCodecs());
    if (!m_deviceInfo.supportedCodecs().empty()) {
        m_format.setCodec(m_deviceInfo.supportedCodecs().at(0));
        m_nearistParams[1] = 0;  // Cập nhật index codec
    }

    setListEndianz(m_deviceInfo.supportedByteOrders());
    if (!m_deviceInfo.supportedByteOrders().empty()) {
        m_format.setByteOrder(m_deviceInfo.supportedByteOrders().at(0));
        m_nearistParams[4] = 0;  // Cập nhật index endian
    }
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
    m_nearistParams = {device, codec, sampleRate, channel, endian};

    qInfo()<< "save params qml: " << m_nearistParams << listChannel();

    // int checkVar = 0;
    m_deviceInfo = cpplistDevices[device];
    m_format.setSampleRate(listSampleRate().at(sampleRate));
    m_format.setChannelCount(listChannel().at(channel));
    m_format.setByteOrder(listEndianz().at(endian));
    m_format.setSampleSize(16);
    m_format.setSampleType(QAudioFormat::SignedInt);

    if (!m_deviceInfo.isFormatSupported(m_format)) {

        setSaveDone(false);

        qWarning() << "Default format not supported -use nearist format";
        m_format = m_deviceInfo.nearestFormat(m_format);

        m_nearistParams[1] = m_deviceInfo.supportedCodecs().indexOf(m_format.codec());
        m_nearistParams[2] = m_deviceInfo.supportedSampleRates().indexOf(m_format.sampleRate());
        m_nearistParams[3] = m_deviceInfo.supportedChannelCounts().indexOf(m_format.channelCount());
        m_nearistParams[4] = m_deviceInfo.supportedByteOrders().indexOf(m_format.byteOrder());

        // Lưu các giá trị vào QSettings
        m_settings.setValue("audio/device", m_nearistParams[0]);
        m_settings.setValue("audio/codec", m_nearistParams[1]);
        m_settings.setValue("audio/sampleRate", m_nearistParams[2]);
        m_settings.setValue("audio/channel", m_nearistParams[3]);
        m_settings.setValue("audio/endian", m_nearistParams[4]);
    }

    qInfo()<< "save params c++: " << m_nearistParams;
    qInfo()<< "save params: " << m_deviceInfo.isFormatSupported(m_format);
    qInfo()<< "channel params: " << m_deviceInfo.supportedChannelCounts().at(m_nearistParams[3]);
}

QAudioDeviceInfo AudioConfig::deviceInfo() const
{
    return m_deviceInfo;
}

QAudioFormat AudioConfig::format() const
{
    return m_format;
}

QList<int> AudioConfig::nearistParams() const
{
    return m_nearistParams;
}

bool AudioConfig::saveDone() const
{
    return m_saveDone;
}

void AudioConfig::setSaveDone(bool newSaveDone)
{
    if (m_saveDone == newSaveDone)
        return;
    m_saveDone = newSaveDone;
    emit saveDoneChanged();
}
