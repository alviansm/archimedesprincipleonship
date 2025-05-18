#include "hydrostatics.h"

Hydrostatics::Hydrostatics() {}

double Hydrostatics::calculateDisplacedVolume(const Vessel& vessel) const
{
    return vessel.mass() * 1000.0 / vessel.waterDensity(); // convert tonnes to kg
}

double Hydrostatics::calculateDraft(const Vessel& vessel) const
{
    double V = calculateDisplacedVolume(vessel);
    return V / (vessel.length() * vessel.breadth()); // simplified prismatic box
}

double Hydrostatics::calculateKB(const Vessel& vessel) const
{
    return 0.53 * calculateDraft(vessel); // simplification for rectangular hull
}

double Hydrostatics::calculateBM(const Vessel& vessel) const
{
    double I = vessel.breadth() * vessel.breadth() * vessel.breadth() * vessel.length() / 12.0;
    double V = calculateDisplacedVolume(vessel);
    return I / V;
}
