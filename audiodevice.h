#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <QObject>
#include <QAudioInput>


class AudioDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioDevice(const QAudioFormat &format, QObject *parent = nullptr);

    void start();
    void stop();

    qreal level() const;

signals:

    // QIODevice interface
protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    const QAudioFormat m_format;
    quint32 m_maxAmplitude = 0;
    qreal m_level = 0.0; // 0.0 <= m_level <= 1.0
};

#endif // AUDIODEVICE_H
