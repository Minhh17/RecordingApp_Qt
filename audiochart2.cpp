#include "audiochart2.h"
#include <QDebug>

CircuitBuffer::CircuitBuffer() : buffer(1000), head(0), tail(0), isFull(false) {}

void CircuitBuffer::add(float value)
{
    buffer[head] = value;
    if (isFull) {
        tail = (tail + 1) % buffer.size();
    }
    head = (head + 1) % buffer.size();
    isFull = head == tail;
}
std::vector<float> CircuitBuffer::getBuffer() const
{
    std::vector<float> result;

    if (isFull) {
        result.insert(result.end(), buffer.begin() + tail, buffer.end());
        result.insert(result.end(), buffer.begin(), buffer.begin() + head);
    } else {
        result.insert(result.end(), buffer.begin(), buffer.begin() + head);
    }

    return result;
}
size_t CircuitBuffer::size() const
{
    return buffer.size();
}

AudioChart2::AudioChart2(QObject *parent) : QObject{parent}
{}

void AudioChart2::onSendChartData(const QByteArray &data)
{
    const int16_t *samples = reinterpret_cast<const int16_t*>(data.constData());
    int sampleCount = data.size() / sizeof(int16_t);

    for (int i = 0; i < sampleCount; ++i) {
        buffer.add(samples[i]/* / 32767.0f*/); // Normalize to [-1, 1]
    }

    // Retrieve data from buffer and prepare it for display
    std::vector<float> bufferedData = buffer.getBuffer();
    QVector<float> displayData;

    int step = qMax(1, static_cast<int>(bufferedData.size()) / displayDataCount);

    for (int i = 0; i < bufferedData.size(); i += step) {
        displayData.append(bufferedData[i]);
    }

    // Send displayData to UI
    emit updateChart(QVariant::fromValue(displayData));
    setDisplayData(QVariant::fromValue(displayData));

    // qInfo()<< "onSendChartData" << displayData.at(0);
}

QVariant AudioChart2::displayData() const
{
    return m_displayData;
}

void AudioChart2::setDisplayData(const QVariant &newDisplayData)
{
    if (m_displayData == newDisplayData)
        return;
    m_displayData = newDisplayData;
    emit displayDataChanged();

    // qInfo()<<"setDisplayData "<<m_displayData.value<QVector<float>>().at(0);
}
