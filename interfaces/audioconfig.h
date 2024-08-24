#ifndef AUDIOCONFIG_H
#define AUDIOCONFIG_H

#include <QObject>
#include <QAudioDeviceInfo>

class AudioConfig : public QObject
{
    Q_OBJECT
public:
    explicit AudioConfig(QObject *parent = nullptr);

signals:

private:
    QAudioDeviceInfo m_deviceInfo;
    QAudioFormat m_settings;

private slots:
    void deviceChanged(int idx);
    void sampleRateChanged(int idx);
    void channelChanged(int idx);
    void codecChanged(int idx);
    // void sampleSizeChanged(int idx);
    // void sampleTypeChanged(int idx);
    void endianChanged(int idx);
};

#endif // AUDIOCONFIG_H
