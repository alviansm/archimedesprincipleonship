#include "vessel.h"

Vessel::Vessel() {}

void Vessel::setDimensions(double L, double B, double H)
{
    m_length = L;
    m_breadth = B;
    m_height = H;
}

void Vessel::setMass(double mass)
{
    m_mass = mass;
}

void Vessel::setKG(double kg)
{
    m_KG = kg;
}

void Vessel::setWaterDensity(double density)
{
    m_waterDensity = density;
}

double Vessel::length() const { return m_length; }
double Vessel::breadth() const { return m_breadth; }
double Vessel::height() const { return m_height; }
double Vessel::mass() const { return m_mass; }
double Vessel::KG() const { return m_KG; }
double Vessel::waterDensity() const { return m_waterDensity; }
