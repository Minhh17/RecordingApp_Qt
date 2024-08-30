#ifndef AUDIOCHART_H
#define AUDIOCHART_H

#include <QObject>
#include <QVector>
#include <QByteArray>
#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>
#include <QPainter>
#include <QPainterPath>

class AudioChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit AudioChart(QQuickPaintedItem *parent = nullptr);

    Q_INVOKABLE void onUpdateChart(const QByteArray &data);

    // void onUpdateChart(const QByteArray &data);
    void drawAxes(QPainter *painter);
    void drawGrid(QPainter *painter);
    void drawLabels(QPainter *painter);

    QVector<QPointF> points() const;
    void setPoints(const QVector<QPointF> &newPoints);

protected:
    void paint(QPainter *painter) override;

signals:
    void chartDataUpdated(const QVector<int> &amplitudes);
    void pointsChanged();

private:
    const QVector<QPointF> convertAudioDataToPoints(const QByteArray &data);

    QVector<QPointF> m_points;

    int m_minX = 0;
    int m_maxX = 1000;  // Ban đầu đặt phạm vi mặc định
    int m_minY = -100;
    int m_maxY = 100;

    void updateAxesRange();

    // QQuickPaintedItem interface

};

#endif // AUDIOCHART_H
