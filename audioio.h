#ifndef AUDIOIO_H
#define AUDIOIO_H

#include <QObject>
#include <QAudioInput>
#include <QIODevice>
#include <QByteArray>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QFile>
#include <QScopedPointer>
#include <audioconfig.h>
#include "audiodevice.h"

class AudioIO : public QObject {
    Q_OBJECT

public:
    explicit AudioIO(QObject *parent = nullptr);
    ~AudioIO();

    void start(const QAudioFormat &format, const QAudioDeviceInfo& device);
    void stop();

signals:
    void sendData(const QByteArray &data);

private slots:
    void onReadyRead();

private:
    QAudioInput *m_audioInput;
    AudioDevice* m_audioIODevice;
    QIODevice* m_audioIODevice2;
    QFile outputFile;
    // QByteArray m_audioData;
};

#endif // AUDIOIO_H
