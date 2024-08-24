#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <QObject>
#include <QFile>

#include "audioio.h"
#include "audioconfig.h"
#include "audiodevice.h"

class AudioController : public QObject
{
    Q_OBJECT
public:
    explicit AudioController(AudioConfig *config, QObject *parent = nullptr);

    Q_PROPERTY(bool recStatus READ recStatus WRITE setRecStatus NOTIFY recStatusChanged FINAL)
    Q_INVOKABLE void startRecord();
    Q_INVOKABLE void pauseRecord();
    Q_INVOKABLE void stopRecord();

    bool recStatus() const;
    void setRecStatus(bool newRecStatus);

public slots:
    void handleDataReady(const QByteArray &data);

signals:

    void recStatusChanged();

private:
    QFile m_outputFile;
    AudioIO* m_audioIO;
    // AudioDevice* m_audioDevice;
    AudioConfig *m_audioConfig;

    bool m_recStatus;
};

#endif // AUDIOCONTROLLER_H
