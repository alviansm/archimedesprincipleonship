#ifndef VESSELINPUTFORM_H
#define VESSELINPUTFORM_H

#include <QDialog>
#include "../app/vessel.h"

class QDoubleSpinBox;
class QPushButton;

class VesselInputForm : public QDialog
{
    Q_OBJECT

public:
    explicit VesselInputForm(QWidget *parent = nullptr);
    void setVessel(const Vessel &vessel);

signals:
    void vesselChanged(const Vessel &vessel);

private slots:
    void applyChanges();

private:
    Vessel m_vessel;

    QDoubleSpinBox *lengthSpin;
    QDoubleSpinBox *breadthSpin;
    QDoubleSpinBox *heightSpin;
    QDoubleSpinBox *massSpin;
    QDoubleSpinBox *kgSpin;
    QDoubleSpinBox *waterDensitySpin;
    QPushButton *applyButton;
};

#endif // VESSELINPUTFORM_H
