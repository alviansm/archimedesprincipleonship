#include "stabilityvisualwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>

StabilityVisualWidget::StabilityVisualWidget(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    m_physics.addTestBox();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        m_physics.step(1.0f / 10.0f, 1); // 10 FPS physics = faster fall
        update();
    });
    m_timer->setSingleShot(false);
    m_timer->start(16); // 60 FPS
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
}

void StabilityVisualWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();  // User clicked widget
}

void StabilityVisualWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void StabilityVisualWidget::dragMoveEvent(QDragMoveEvent* event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void StabilityVisualWidget::dropEvent(QDropEvent* event)
{
    if (!event->mimeData()->hasText())
        return;

    QString label = event->mimeData()->text();

    // Create a new cargo item
    QPoint snapped = CargoItemWidget::snapToGrid(event->position().toPoint());
    CargoItemWidget* newCargo = new CargoItemWidget(label, true, this);
    newCargo->move(snapped);
    newCargo->show();
    newCargo->raise();

    event->acceptProposedAction();
}
