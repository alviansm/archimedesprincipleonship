#include "stabilityvisualwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>

StabilityVisualWidget::StabilityVisualWidget(QWidget *parent)
    : QWidget(parent)
{
    // Set some default vessel values
    m_vessel.setDimensions(100, 20, 10);  // L, B, H
    m_vessel.setMass(5000);
    m_vessel.setKG(5);
    m_vessel.setWaterDensity(1025);
    updateStability();
}

void StabilityVisualWidget::setVessel(const Vessel &vessel)
{
    m_vessel = vessel;
    updateStability();
}

void StabilityVisualWidget::updateStability()
{
    m_engine.setVessel(m_vessel);
    m_engine.compute();
    update(); // repaint widget
}

void StabilityVisualWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Scaled dimensions
    double boxWidth = m_vessel.breadth() * m_scale;
    double boxHeight = m_vessel.height() * m_scale;
    double draft = m_engine.getDraft() * m_scale;

    // Center the box
    double x = (width() - boxWidth) / 2.0;
    double y = (height() - boxHeight) / 2.0;
    double waterLevelY = y + boxHeight - draft;

    // --- [1] Draw Transparent Sea Background FIRST
    QColor seaColor(100, 149, 237, 120);  // RGBA with transparency
    painter.setPen(Qt::NoPen);
    painter.setBrush(seaColor);
    painter.drawRect(0, waterLevelY, width(), height() - waterLevelY);

    // --- [2] Draw the Hull Box NEXT
    QRectF hullRect(x, y, boxWidth, boxHeight);
    painter.setPen(Qt::black);
    painter.setBrush(QColor(200, 200, 200));  // solid gray
    painter.drawRect(hullRect);

    // --- [3] Optional: Text Information
    painter.setPen(Qt::black);
    painter.drawText(QPointF(10, 20), QString("GM: %1 m").arg(m_engine.getGM(), 0, 'f', 2));
    painter.drawText(QPointF(10, 40), m_engine.getStabilityCondition());
    painter.drawText(QPointF(10, 60), QString("Draft: %1 m").arg(m_engine.getDraft(), 0, 'f', 2));
    painter.drawText(QPointF(10, 80), QString("KB: %1 m").arg(m_engine.getKB(), 0, 'f', 2));
    painter.drawText(QPointF(10, 100), QString("KM: %1 m").arg(m_engine.getKM(), 0, 'f', 2));

    // --- [3] Draw Vertical Markers
    double cx = x + boxWidth / 2.0;  // center X of hull

    // KG - Center of Gravity (Red Circle)
    double kgY = y + m_vessel.KG() * m_scale;
    painter.setBrush(Qt::red);
    painter.setPen(Qt::black);
    painter.drawEllipse(QPointF(cx, kgY), 4, 4);
    painter.drawText(cx + 6, kgY + 4, "KG");

    // KB - Center of Buoyancy (Blue Circle)
    double kbY = y + boxHeight - m_engine.getKB() * m_scale;
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::black);
    painter.drawEllipse(QPointF(cx, kbY), 4, 4);
    painter.drawText(cx + 6, kbY + 4, "KB");

    // KM - Metacenter (Black Triangle)
    double kmY = y + boxHeight - m_engine.getKM() * m_scale;
    QPointF triangle[3] = {
        QPointF(cx, kmY - 5),
        QPointF(cx - 4, kmY + 4),
        QPointF(cx + 4, kmY + 4)
    };
    painter.setBrush(Qt::black);
    painter.drawPolygon(triangle, 3);
    painter.drawText(cx + 6, kmY, "KM");

    // Draft - Dashed Waterline Marker (across hull)
    painter.setPen(QPen(Qt::darkCyan, 1, Qt::DashLine));
    painter.drawLine(x, waterLevelY, x + boxWidth, waterLevelY);
    painter.drawText(x + boxWidth + 5, waterLevelY + 4, "Draft");
}

void StabilityVisualWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();  // User clicked widget
}
