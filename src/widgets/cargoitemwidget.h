#ifndef CARGOITEMWIDGET_H
#define CARGOITEMWIDGET_H

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>
#include <QLabel>
#include <QWidget>

#include "./stabilityvisualwidget.h"

// src/widgets/cargoitemwidget.h

class CargoItemWidget : public QLabel {
    Q_OBJECT

public:
    explicit CargoItemWidget(const QString& label, bool isMovable = false, QWidget* parent = nullptr);

    static QPoint snapToGrid(const QPoint& pos);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool m_isMovable = false;
    QPoint m_dragStartPos;

};


#endif // CARGOITEMWIDGET_H
