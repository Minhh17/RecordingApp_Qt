#ifndef AUDIOCHART2_H
#define AUDIOCHART2_H

#include <QObject>
#include <QVector>
#include <QVariant>
#include <vector>
#include <algorithm>

class CircuitBuffer {

public:
    explicit CircuitBuffer();

    void add(float value);
    std::vector<float> getBuffer() const;

    size_t size() const;

private:
    std::vector<float> buffer;
    size_t head, tail;
    bool isFull;
};


class AudioChart2 : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QVariant displayData READ displayData WRITE setDisplayData NOTIFY displayDataChanged FINAL)
    explicit AudioChart2(QObject *parent = nullptr);

    QVariant displayData() const;
    void setDisplayData(const QVariant &newDisplayData);

public slots:
    void onSendChartData(const QByteArray &data);

signals:
    void updateChart(QVariant displayData);
    void displayDataChanged();

private:
    CircuitBuffer buffer;
    int displayDataCount = 500;
    QVariant m_displayData = {};
};

#endif // AUDIOCHART2_H
