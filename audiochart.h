#ifndef AUDIOCHART_H
#define AUDIOCHART_H

#include <QObject>
#include <QQmlEngine>

class AudioChart : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit AudioChart(QObject *parent = nullptr);

signals:
};

#endif // AUDIOCHART_H
