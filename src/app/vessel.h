#ifndef VESSEL_H
#define VESSEL_H

class Vessel
{
public:
    Vessel();

    void setDimensions(double L, double B, double H);
    void setMass(double mass);
    void setKG(double kg);
    void setWaterDensity(double density);

    double length() const;
    double breadth() const;
    double height() const;
    double mass() const;
    double KG() const;
    double waterDensity() const;

private:
    double m_length = 0.0;     // m
    double m_breadth = 0.0;    // m
    double m_height = 0.0;     // m
    double m_mass = 0.0;       // tonnes
    double m_KG = 0.0;         // vertical center of gravity (m)
    double m_waterDensity = 1025.0; // default seawater (kg/m³)
};

#endif // VESSEL_H
