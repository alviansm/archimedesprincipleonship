#ifndef STABILITYVISUALWIDGET_H
#define STABILITYVISUALWIDGET_H

#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QtMath>
#include <cmath>

#include "../app/stabilityengine.h"
#include "../physics/physicsengine.h"

class CargoItemWidget;
class StabilityVisualWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StabilityVisualWidget(QWidget *parent = nullptr);

    void setVessel(const Vessel &vessel);
    void updateStability();
    QPoint findNearestValidPosition(CargoItemWidget* cargo, QPoint desiredPos);

    Vessel vessel() const { return m_vessel; }

public slots:
    void animateWater();

signals:
    void clicked();  // Signal to open input dialog

// QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;


private:
    StabilityEngine m_engine;
    Vessel m_vessel;

    // Visualization helpers
    double m_margin = 20.0;
    double m_scale = 20.0; // pixels per meter

    QTimer m_animationTimer;
    double m_waveOffset = 0.0;

    // Physics Engine
    PhysicsEngine m_physics;
    QTimer* m_timer;

};

#endif // STABILITYVISUALWIDGET_H
