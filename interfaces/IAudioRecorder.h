#ifndef IAUDIORECORDER_H
#define IAUDIORECORDER_H

#include <QUrl>

class IAudioRecorder {
public:
    virtual ~IAudioRecorder() = default;
    virtual void startRecord(const QString &filePath) = 0;
    virtual void stopRecord() = 0;
    virtual void endRecord() = 0;

};

#endif // IAUDIORECORDER_H
