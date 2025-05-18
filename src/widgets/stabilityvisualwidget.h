#ifndef STABILITYVISUALWIDGET_H
#define STABILITYVISUALWIDGET_H

#include <QWidget>
#include "../app/stabilityengine.h"

class StabilityVisualWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StabilityVisualWidget(QWidget *parent = nullptr);

    void setVessel(const Vessel &vessel);
    void updateStability();

    Vessel vessel() const { return m_vessel; }

signals:
    void clicked();  // Signal to open input dialog

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    StabilityEngine m_engine;
    Vessel m_vessel;

    // Visualization helpers
    double m_margin = 20.0;
    double m_scale = 20.0; // pixels per meter
};

#endif // STABILITYVISUALWIDGET_H
