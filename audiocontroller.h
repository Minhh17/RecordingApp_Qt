#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <QObject>
#include <QFile>
#include <QTimer>

#include "audioio.h"
#include "audioconfig.h"
#include "audiodevice.h"
#include "audiofile.h"
#include "audiochart.h"
#include "audiochart2.h"

class AudioController : public QObject
{
    Q_OBJECT
public:
    explicit AudioController(AudioConfig *config, QObject *parent = nullptr);
    ~AudioController();

    Q_PROPERTY(bool recStatus READ recStatus WRITE setRecStatus NOTIFY recStatusChanged FINAL)
    Q_INVOKABLE void startRecord();
    Q_INVOKABLE void pauseRecord();
    Q_INVOKABLE void stopRecord();

    bool recStatus() const;
    void setRecStatus(bool newRecStatus);

public slots:
    void handleDataReady(const QByteArray &data);
signals:

    void sendDataChart(const QByteArray &data);
    void recStatusChanged();

private:
    // QFile m_outputFile;
    AudioIO* m_audioIO;
    // AudioDevice* m_audioDevice;
    AudioConfig *m_audioConfig;
    AudioFile m_audioFile;
    AudioChart* m_audioChart;
    AudioChart2* m_audioChart2;

    bool m_recStatus;

};

#endif // AUDIOCONTROLLER_H
