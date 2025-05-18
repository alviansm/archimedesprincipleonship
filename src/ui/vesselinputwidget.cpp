#include "vesselinputwidget.h"
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QPushButton>

VesselInputWidget::VesselInputWidget(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *form = new QFormLayout(this);

    lengthSpin = new QDoubleSpinBox; lengthSpin->setRange(1, 500); lengthSpin->setValue(100);
    breadthSpin = new QDoubleSpinBox; breadthSpin->setRange(1, 100); breadthSpin->setValue(20);
    heightSpin = new QDoubleSpinBox; heightSpin->setRange(1, 50); heightSpin->setValue(10);
    massSpin = new QDoubleSpinBox; massSpin->setRange(1, 100000); massSpin->setValue(5000);
    kgSpin = new QDoubleSpinBox; kgSpin->setRange(0, 50); kgSpin->setValue(5);
    waterDensitySpin = new QDoubleSpinBox; waterDensitySpin->setRange(800, 1500); waterDensitySpin->setValue(1025);

    form->addRow("Length (m)", lengthSpin);
    form->addRow("Breadth (m)", breadthSpin);
    form->addRow("Height (m)", heightSpin);
    form->addRow("Mass (tonnes)", massSpin);
    form->addRow("KG (m)", kgSpin);
    form->addRow("Water SG (kg/m³)", waterDensitySpin);

    applyButton = new QPushButton("Apply", this);
    form->addWidget(applyButton);
    connect(applyButton, &QPushButton::clicked, this, &VesselInputWidget::emitVessel);
}

void VesselInputWidget::emitVessel()
{
    Vessel vessel;
    vessel.setDimensions(lengthSpin->value(), breadthSpin->value(), heightSpin->value());
    vessel.setMass(massSpin->value());
    vessel.setKG(kgSpin->value());
    vessel.setWaterDensity(waterDensitySpin->value());
    emit vesselUpdated(vessel);
}
