#ifndef VESSELINPUTWIDGET_H
#define VESSELINPUTWIDGET_H

#include <QWidget>
#include "../app/vessel.h"
class QDoubleSpinBox;
class QPushButton;

class VesselInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VesselInputWidget(QWidget *parent = nullptr);

signals:
    void vesselUpdated(const Vessel& vessel);

private slots:
    void emitVessel();

private:
    QDoubleSpinBox *lengthSpin;
    QDoubleSpinBox *breadthSpin;
    QDoubleSpinBox *heightSpin;
    QDoubleSpinBox *massSpin;
    QDoubleSpinBox *kgSpin;
    QDoubleSpinBox *waterDensitySpin;
    QPushButton *applyButton;
};

#endif // VESSELINPUTWIDGET_H
