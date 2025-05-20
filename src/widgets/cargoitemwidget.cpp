#include "cargoitemwidget.h"

const int GRID_SIZE = 4;

CargoItemWidget::CargoItemWidget(const QString& label, bool isMovable, QWidget* parent)
    : QLabel(label, parent), m_isMovable(isMovable)
{
    setFixedSize(24, 24);
    setAlignment(Qt::AlignCenter);
    setStyleSheet(R"(
        background-color: #3498db;
        border: 2px solid #21618c;
        border-radius: 6px;
        color: white;
        font-weight: bold;
        font-size: 14px;
    )");
    setAttribute(Qt::WA_DeleteOnClose);
}

QPoint CargoItemWidget::snapToGrid(const QPoint &pos)
{
    return QPoint(
        (pos.x() / GRID_SIZE) * GRID_SIZE,
        (pos.y() / GRID_SIZE) * GRID_SIZE
    );
}

void CargoItemWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        m_dragStartPos = event->pos();
}

void CargoItemWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (m_isMovable) {
            // Move inside parent widget
            QPoint diff = event->pos() - m_dragStartPos;
            QPoint newPos = pos() + diff;
            move(snapToGrid(newPos));
        } else {
            // Toolbar drag → standard Qt drag
            if ((event->pos() - m_dragStartPos).manhattanLength() < QApplication::startDragDistance())
                return;

            QDrag* drag = new QDrag(this);
            QMimeData* mimeData = new QMimeData;
            mimeData->setText(text());
            drag->setMimeData(mimeData);
            drag->exec(Qt::CopyAction);
        }
    }
}

