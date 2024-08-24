    #ifndef AUDIOCONFIG_H
#define AUDIOCONFIG_H

#include <QObject>
#include <QDebug>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QVariantMap>
#include <QStringList>

class AudioConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList listDevices READ listDevices WRITE setListDevices NOTIFY listDevicesChanged FINAL)
    Q_PROPERTY(QList<int> listSampleRate READ listSampleRate WRITE setListSampleRate NOTIFY listSampleRateChanged FINAL)
    Q_PROPERTY(QList<int> listChannel READ listChannel WRITE setListChannel NOTIFY listChannelChanged FINAL)
    Q_PROPERTY(QStringList listCodecs READ listCodecs WRITE setListCodecs NOTIFY listCodecsChanged FINAL)
    Q_PROPERTY(QList<QAudioFormat::Endian> listEndianz READ listEndianz WRITE setListEndianz NOTIFY listEndianzChanged FINAL)

public:
    explicit AudioConfig(QObject *parent = nullptr);

    QStringList listDevices() const;
    void setListDevices(const QStringList &newListDevices);

    QList<int> listSampleRate() const;
    void setListSampleRate(const QList<int> &newListSampleRate);

    QList<int> listChannel() const;
    void setListChannel(const QList<int> &newListChannel);

    QStringList listCodecs() const;
    void setListCodecs(const QStringList &newListCodecs);

    QList<QAudioFormat::Endian> listEndianz() const;
    void setListEndianz(const QList<QAudioFormat::Endian> &newListEndianz);

    Q_INVOKABLE void changeDevice(int idx);

    Q_INVOKABLE void saveConfig(int codec, int sampleRate, int channel, int endian);

    QAudioDeviceInfo deviceInfo() const;

    QAudioFormat settings() const;

signals:
    void listCodecsChanged();
    void listSampleRateChanged();
    void listChannelChanged();
    void listEndianzChanged();
    void listDevicesChanged();

private:
    QAudioDeviceInfo m_deviceInfo;
    QAudioFormat m_settings;
    QList<QAudioDeviceInfo> cpplistDevices;

    QStringList listDevicesName;
    QStringList m_listDevices;
    QList<int> m_listSampleRate;
    QList<int> m_listChannel;
    QStringList m_listCodecs;
    QList<QAudioFormat::Endian> m_listEndianz;

};

#endif // AUDIOCONFIG_H
