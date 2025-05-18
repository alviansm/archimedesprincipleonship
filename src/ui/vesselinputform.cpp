#include "vesselinputform.h"
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialogButtonBox>

VesselInputForm::VesselInputForm(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Edit Vessel Parameters");

    lengthSpin = new QDoubleSpinBox; lengthSpin->setRange(1, 500);
    breadthSpin = new QDoubleSpinBox; breadthSpin->setRange(1, 100);
    heightSpin = new QDoubleSpinBox; heightSpin->setRange(1, 100);
    massSpin = new QDoubleSpinBox; massSpin->setRange(1, 100000);
    kgSpin = new QDoubleSpinBox; kgSpin->setRange(0, 50);
    waterDensitySpin = new QDoubleSpinBox; waterDensitySpin->setRange(900, 1100);

    QFormLayout *form = new QFormLayout;
    form->addRow("Length (m):", lengthSpin);
    form->addRow("Breadth (m):", breadthSpin);
    form->addRow("Height (m):", heightSpin);
    form->addRow("Mass (tonnes):", massSpin);
    form->addRow("KG (m):", kgSpin);
    form->addRow("Water SG (kg/m³):", waterDensitySpin);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &VesselInputForm::applyChanges);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &VesselInputForm::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(form);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

void VesselInputForm::setVessel(const Vessel &vessel)
{
    m_vessel = vessel;
    lengthSpin->setValue(vessel.length());
    breadthSpin->setValue(vessel.breadth());
    heightSpin->setValue(vessel.height());
    massSpin->setValue(vessel.mass());
    kgSpin->setValue(vessel.KG());
    waterDensitySpin->setValue(vessel.waterDensity());
}

void VesselInputForm::applyChanges()
{
    m_vessel.setDimensions(lengthSpin->value(), breadthSpin->value(), heightSpin->value());
    m_vessel.setMass(massSpin->value());
    m_vessel.setKG(kgSpin->value());
    m_vessel.setWaterDensity(waterDensitySpin->value());

    emit vesselChanged(m_vessel);
    accept();  // optional, closes the dialog
}
