#include "stabilityvisualwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QPropertyAnimation>

#include "./widgets/cargoitemwidget.h"

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

QPoint StabilityVisualWidget::findNearestValidPosition(CargoItemWidget *cargo, QPoint desiredPos)
{
    QRect targetRect(desiredPos, cargo->size());

    // Try down-stepping to find lowest non-overlapping position
    const int maxY = height() - cargo->height();

    for (int y = desiredPos.y(); y <= maxY; y += 1) {
        QRect testRect(QPoint(desiredPos.x(), y), cargo->size());

        bool collision = false;

        for (QObject* child : children()) {
            auto* other = qobject_cast<CargoItemWidget*>(child);
            if (other && other != cargo) {
                QRect otherRect = QRect(other->pos(), other->size());
                if (testRect.intersects(otherRect)) {
                    collision = true;
                    break;
                }
            }
        }

        if (collision) {
            return QPoint(desiredPos.x(), y - 1);  // just before collision
        }
    }

    return QPoint(desiredPos.x(), maxY);
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

    QPoint rawPos = event->position().toPoint();
    QPoint snapped = CargoItemWidget::snapToGrid(rawPos);

    // Create cargo first
    CargoItemWidget* newCargo = new CargoItemWidget(label, true, this);

    // Now calculate valid position
    QPoint validPos = findNearestValidPosition(newCargo, snapped);

    newCargo->move(snapped);  // Start at snapped position (user's drop intent)

    QPropertyAnimation* anim = new QPropertyAnimation(newCargo, "pos");
    anim->setDuration(300);  // 300 ms fall
    anim->setStartValue(snapped);
    anim->setEndValue(validPos);
    anim->setEasingCurve(QEasingCurve::OutBounce);  // Optional: feels physical
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    newCargo->show();
    newCargo->raise();

    event->acceptProposedAction();

    updateStability();  // Optional but recommended here too
}

