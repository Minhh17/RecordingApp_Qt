#include "audiochart.h"
#include <QDebug>

AudioChart::AudioChart(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    this->setHeight(700);
    this->setWidth(300);
    m_points.append(QPointF(0, 0));
    m_points.append(QPointF(100, 100));

}

void AudioChart::onUpdateChart(const QByteArray &data)
{
    qDebug() <<"onUpdateChart"<<data.at(0);
    // m_points = convertAudioDataToPoints(data);

    // Giữ kích thước của m_points ở mức cố định để tránh quá tải
    // const int maxPoints = 600;
    // if (points().size() + newPoints.size() > maxPoints) {
    //     points() = points().mid(newPoints.size());
    // }

    // setPoints(newPoints);

    qDebug() <<"onUpdateChart"<<m_points.size();
    qDebug() <<"onUpdateChart"<<points().size();
    updateAxesRange();

    update();

}

void AudioChart::drawAxes(QPainter *painter)
{
    QPen axisPen(Qt::black, 2);
    painter->setPen(axisPen);

    // Vẽ trục X và trục Y
    painter->drawLine(50, height() - 50, width() - 50, height() - 50); // Trục X
    painter->drawLine(50, 50, 50, height() - 50); // Trục Y
}


void AudioChart::updateAxesRange()
{
    if (m_points.isEmpty())
        return;

    m_minX = m_points.first().x();
    m_maxX = m_points.last().x();

    m_minY = m_points.first().y();
    m_maxY = m_minY;

    for (const QPointF &point : m_points) {
        if (point.y() < m_minY)
            m_minY = point.y();
        if (point.y() > m_maxY)
            m_maxY = point.y();
    }

    // Thêm một chút margin để dữ liệu không chạm sát trục
    float marginY = (m_maxY - m_minY) * 0.1;
    m_minY -= marginY;
    m_maxY += marginY;
}

void AudioChart::drawGrid(QPainter *painter)
{
    QPen gridPen(Qt::gray, 1, Qt::DotLine);
    painter->setPen(gridPen);

    int gridSpacingX = (width() - 100) / 10;  // 10 khoảng chia trên trục X
    int gridSpacingY = (height() - 100) / 10; // 10 khoảng chia trên trục Y

    // Vẽ lưới theo trục X
    for (int i = 1; i <= 10; ++i) {
        int x = 50 + i * gridSpacingX;
        painter->drawLine(x, 50, x, height() - 50);
    }

    // Vẽ lưới theo trục Y
    for (int i = 1; i <= 10; ++i) {
        int y = 50 + i * gridSpacingY;
        painter->drawLine(50, y, width() - 50, y);
    }

    // Vẽ số đo trên trục
    painter->setPen(Qt::black);
    for (int i = 1; i <= 10; ++i) {
        // Số đo trên trục X
        int x = 50 + i * gridSpacingX;
        painter->drawText(x - 10, height() - 30, QString::number(m_minX + i * (m_maxX - m_minX) / 10.0, 'f', 2));

        // Số đo trên trục Y
        int y = 50 + i * gridSpacingY;
        painter->drawText(20, height() - 50 - i * gridSpacingY + 5, QString::number(m_minY + i * (m_maxY - m_minY) / 10.0, 'f', 2));
    }
}

const QVector<QPointF> AudioChart::convertAudioDataToPoints(const QByteArray &data)
{
    QVector<QPointF> points;
    for (int i = 0; i < data.size(); i += 2) {
        int16_t sample = *reinterpret_cast<const int16_t*>(data.data() + i);
        points.append(QPointF(i / 2, sample));
    }
    return points;
}

QVector<QPointF> AudioChart::points() const
{
    return m_points;
}

void AudioChart::setPoints(const QVector<QPointF> &newPoints)
{
    if (m_points == newPoints)
        return;
    m_points = newPoints;
    emit pointsChanged();
}

void AudioChart::paint(QPainter *painter)
{
    qDebug()<<"paint-AudioChart" << points().size();

    painter->setRenderHint(QPainter::Antialiasing);

    // Vẽ các trục
    drawAxes(painter);

    // Vẽ lưới
    drawGrid(painter);

    // Vẽ đường biểu đồ từ các điểm lưu trữ
    painter->setPen(QPen(Qt::blue, 2));

    // Dịch chuyển điểm sao cho phù hợp với phạm vi trục
    QPainterPath path;
    const int offsetX = 50;
    const int offsetY = 50;
    const int chartWidth = width() - 100;
    const int chartHeight = height() - 100;
    const int maxAmplitude = 32767; // Giá trị max của int16_t

    for (int i = 0; i < m_points.size(); ++i) {
        QPointF point = m_points[i];
        float x = offsetX + (point.x() / 1000.0f) * chartWidth;
        float y = offsetY + chartHeight / 2 - (point.y() / maxAmplitude) * (chartHeight / 2);
        if (i == 0) {
            path.moveTo(x, y);
        } else {
            path.lineTo(x, y);
        }
    }
    painter->drawPath(path);
}


