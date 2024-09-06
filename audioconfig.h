    #ifndef AUDIOCONFIG_H
#define AUDIOCONFIG_H

#include <QObject>
#include <QDebug>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QVariantMap>
#include <QStringList>
#include <QSettings>

class AudioConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList listDevices READ listDevices WRITE setListDevices NOTIFY listDevicesChanged FINAL)
    Q_PROPERTY(QList<int> listSampleRate READ listSampleRate WRITE setListSampleRate NOTIFY listSampleRateChanged FINAL)
    Q_PROPERTY(QList<int> listChannel READ listChannel WRITE setListChannel NOTIFY listChannelChanged FINAL)
    Q_PROPERTY(QStringList listCodecs READ listCodecs WRITE setListCodecs NOTIFY listCodecsChanged FINAL)
    Q_PROPERTY(QList<QAudioFormat::Endian> listEndianz READ listEndianz WRITE setListEndianz NOTIFY listEndianzChanged FINAL)

    Q_PROPERTY(QList<int> nearistParams READ nearistParams NOTIFY nearistParamsChanged FINAL)

    Q_PROPERTY(bool saveDone READ saveDone WRITE setSaveDone NOTIFY saveDoneChanged FINAL)

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

    Q_INVOKABLE void saveConfig(int device, int codec, int sampleRate, int channel, int endian);

    QAudioDeviceInfo deviceInfo() const;

    QAudioFormat format() const;

    QList<int> nearistParams() const;

    bool saveDone() const;
    void setSaveDone(bool newSaveDone);

signals:
    void listCodecsChanged();
    void listSampleRateChanged();
    void listChannelChanged();
    void listEndianzChanged();
    void listDevicesChanged();

    void nearistParamsChanged();

    void saveDoneChanged();

private:
    QAudioDeviceInfo m_deviceInfo;
    QAudioFormat m_format;
    QList<QAudioDeviceInfo> cpplistDevices;

    QStringList listDevicesName;
    QStringList m_listDevices;
    QList<int> m_listSampleRate;
    QList<int> m_listChannel;
    QStringList m_listCodecs;
    QList<QAudioFormat::Endian> m_listEndianz;

    QList<int> m_nearistParams = {0,0,0,0,0};

    QSettings m_settings;
    bool m_saveDone = true;
};

#endif // AUDIOCONFIG_H
