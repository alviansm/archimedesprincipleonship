#include "stabilityvisualwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>

StabilityVisualWidget::StabilityVisualWidget(QWidget *parent)
    : QWidget(parent)
{
    m_physics.addTestBox();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        // m_physics.step();
        m_physics.step(1.0f / 10.0f, 1); // 10 FPS physics = faster fall
        update();
    });
    m_timer->setSingleShot(false);
    m_timer->start(16); // 60 FPS

    // Set some default vessel values
    // m_vessel.setDimensions(100, 20, 10);  // L, B, H
    // m_vessel.setMass(5000);
    // m_vessel.setKG(5);
    // m_vessel.setWaterDensity(1025);
    // updateStability();

    // // Timer setup
    // connect(&m_animationTimer, &QTimer::timeout, this, &StabilityVisualWidget::animateWater);
    // m_animationTimer.start(30);
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

void StabilityVisualWidget::animateWater()
{
    m_waveOffset += 0.05;
    if (m_waveOffset > 2 * M_PI) m_waveOffset = 0;
    update(); // repaint
}

void StabilityVisualWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor("#dce4ec"));

    // const float scale = 20.0f;
    const float scale = 40.0f;
    const float halfSize = 1.0f * scale;

    for (const b2BodyId& bodyId : m_physics.dynamicBodies()) {
        b2Vec2 pos = b2Body_GetPosition(bodyId);
        b2Rot rot = b2Body_GetRotation(bodyId);
        float angle = atan2f(rot.s, rot.c); // in radians

        QPointF center(pos.x * scale, pos.y * scale);
        QRectF box(-halfSize, -halfSize, 2 * halfSize, 2 * halfSize);

        painter.save();
        painter.translate(center);
        painter.rotate(angle * 180.0 / M_PI); // Box2D gives radians, Qt wants degrees
        painter.setBrush(Qt::darkGray);
        painter.setPen(Qt::black);
        painter.drawRect(box);  // Draw centered at origin after transformation
        painter.restore();
    }

    painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
    painter.drawLine(0, 17.0f * scale, width(), 17.0f * scale);

    // painter.setPen(Qt::blue);
    // painter.drawEllipse(center, 2, 2);
}

// void StabilityVisualWidget::paintEvent(QPaintEvent *event)
// {
//     Q_UNUSED(event);
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     // Scaled dimensions
//     double boxWidth = m_vessel.breadth() * m_scale;
//     double boxHeight = m_vessel.height() * m_scale;
//     double draft = m_engine.getDraft() * m_scale;

//     // Center the box
//     double x = (width() - boxWidth) / 2.0;
//     double y = (height() - boxHeight) / 2.0;
//     double waterLevelY = y + boxHeight - draft;

//     // --- [1] Draw Transparent Sea Background FIRST
//     // QColor seaColor(100, 149, 237, 120);  // RGBA with transparency
//     // painter.setPen(Qt::NoPen);
//     // painter.setBrush(seaColor);
//     // painter.drawRect(0, waterLevelY, width(), height() - waterLevelY);

//     // Draw water with animated sine wave effect
//     QPainterPath wavePath;
//     int waveHeight = 2;  // pixels
//     int waveCount = 1;

//     wavePath.moveTo(0, waterLevelY);

//     for (int x = 0; x <= width(); ++x) {
//         double y = waterLevelY + std::sin((x / (double)width()) * waveCount * 2 * M_PI + m_waveOffset) * waveHeight;
//         wavePath.lineTo(x, y);
//     }
//     wavePath.lineTo(width(), height());
//     wavePath.lineTo(0, height());
//     wavePath.closeSubpath();

//     painter.setBrush(QColor(100, 149, 237, 120)); // translucent blue
//     painter.setPen(Qt::NoPen);
//     painter.drawPath(wavePath);

//     // --- [2] Draw the Hull Box NEXT
//     QRectF hullRect(x, y, boxWidth, boxHeight);
//     painter.setPen(Qt::black);
//     painter.setBrush(QColor(200, 200, 200));  // solid gray
//     painter.drawRect(hullRect);

//     // --- [3] Optional: Text Information
//     painter.setPen(Qt::black);
//     painter.drawText(QPointF(10, 20), QString("GM: %1 m").arg(m_engine.getGM(), 0, 'f', 2));
//     painter.drawText(QPointF(10, 40), m_engine.getStabilityCondition());
//     painter.drawText(QPointF(10, 60), QString("Draft: %1 m").arg(m_engine.getDraft(), 0, 'f', 2));
//     painter.drawText(QPointF(10, 80), QString("KB: %1 m").arg(m_engine.getKB(), 0, 'f', 2));
//     painter.drawText(QPointF(10, 100), QString("KM: %1 m").arg(m_engine.getKM(), 0, 'f', 2));

//     // Draft - Dashed Waterline Marker (across hull)
//     // painter.setPen(QPen(Qt::darkCyan, 1, Qt::DashLine));
//     // painter.drawLine(x, waterLevelY, x + boxWidth, waterLevelY);
//     // painter.drawText(x + boxWidth + 5, waterLevelY + 4, "Draft");

//     QLinearGradient waterGradient(0, waterLevelY, 0, height());
//     waterGradient.setColorAt(0.0, QColor(100, 149, 237, 140));
//     waterGradient.setColorAt(1.0, QColor(70, 130, 180, 90));
//     painter.setBrush(waterGradient);
//     painter.setPen(Qt::NoPen);
//     painter.drawPath(wavePath);

//     // --- [4] Draw Vertical Markers
//     double cx = x + boxWidth / 2.0;  // center X of hull

//     // KG - Center of Gravity (Red Circle)
//     double kgY = y + m_vessel.KG() * m_scale;
//     painter.setBrush(Qt::red);
//     painter.setPen(Qt::black);
//     painter.drawEllipse(QPointF(cx, kgY), 4, 4);
//     painter.drawText(cx + 6, kgY + 4, "KG");

//     // KB - Center of Buoyancy (Blue Circle)
//     double kbY = y + boxHeight - m_engine.getKB() * m_scale;
//     painter.setBrush(Qt::blue);
//     painter.setPen(Qt::black);
//     painter.drawEllipse(QPointF(cx, kbY), 4, 4);
//     painter.drawText(cx + 6, kbY + 4, "KB");

//     // KM - Metacenter (Black Triangle)
//     double kmY = y + boxHeight - m_engine.getKM() * m_scale;
//     QPointF triangle[3] = {
//         QPointF(cx, kmY - 5),
//         QPointF(cx - 4, kmY + 4),
//         QPointF(cx + 4, kmY + 4)
//     };
//     painter.setBrush(Qt::black);
//     painter.drawPolygon(triangle, 3);
//     painter.drawText(cx + 6, kmY, "KM");
// }

void StabilityVisualWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();  // User clicked widget
}
