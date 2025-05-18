#ifndef STABILITYENGINE_H
#define STABILITYENGINE_H

#include "vessel.h"
#include "hydrostatics.h"

#include <QString>

class StabilityEngine
{
public:
    StabilityEngine();

    void setVessel(const Vessel& vessel);
    void compute();

    double getDraft() const;
    double getKB() const;
    double getBM() const;
    double getKM() const;
    double getGM() const;
    QString getStabilityCondition() const;

private:
    Vessel m_vessel;
    Hydrostatics m_hydrostatics;

    double m_draft = 0.0;
    double m_KB = 0.0;
    double m_BM = 0.0;
    double m_KM = 0.0;
    double m_GM = 0.0;
};

#endif // STABILITYENGINE_H
