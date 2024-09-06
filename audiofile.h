#include <QFile>
#include <QDataStream>
#include <QAudioFormat>
#include <QByteArray>
#include <QDir>

class AudioFile {
public:
    AudioFile();
    ~AudioFile();

    bool startRecording(const QString &fileName, const QAudioFormat &format);
    void writeAudioData(const QByteArray &data);
    void stopRecording();

    // For playback
    bool openForPlayback(const QString &fileName);
    QByteArray readAudioData();

private:
    QFile wavFile;
    QAudioFormat audioFormat;
    qint64 dataSize;

    void writeWavHeader();
    void finalizeWavHeader();
};
