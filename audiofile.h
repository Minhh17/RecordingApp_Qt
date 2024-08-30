#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <QFile>
#include <QByteArray>

class AudioFile : public QObject
{
    Q_OBJECT

public:
    explicit AudioFile(const QString &filePath);
    ~AudioFile();

    void writeData(const QByteArray &data);
    void closeFile();

private:
    QFile outputFile;
    void writeWavHeader();
    void updateWavHeader();
};

#endif // AUDIOFILE_H
