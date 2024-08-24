#ifndef AUDIOPROCESSING_H
#define AUDIOPROCESSING_H

#include <QObject>

class AudioProcessing : public QObject
{
    Q_OBJECT
public:
    explicit AudioProcessing(QObject *parent = nullptr);

signals:
};

#endif // AUDIOPROCESSING_H
