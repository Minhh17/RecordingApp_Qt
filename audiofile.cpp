#include "audiofile.h"
#include <QDebug>

AudioFile::AudioFile(const QString &filePath) : outputFile(filePath)
{
    if (!outputFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Cannot open file for writing";
    } else {
        writeWavHeader(); // Write initial WAV header
    }
}

AudioFile::~AudioFile()
{
    updateWavHeader(); // Update the WAV header with final sizes
    outputFile.close();
}

void AudioFile::writeData(const QByteArray &data)
{
    if (outputFile.isOpen()) {
        outputFile.write(data);
    } else {
        qWarning() << "File is not open for writing";
    }
}

void AudioFile::closeFile()
{
    if (outputFile.isOpen()) {
        updateWavHeader();
        outputFile.close();
    }
}

void AudioFile::writeWavHeader()
{
    // Write the WAV header (with placeholders for sizes)
    QByteArray header;
    // (Fill in with appropriate WAV header data)
    outputFile.write(header);
}

void AudioFile::updateWavHeader()
{
    // Update the header with the correct sizes
    // (You may need to reopen the file in ReadWrite mode to update the header)
}
