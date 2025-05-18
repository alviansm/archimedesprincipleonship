#include "stabilityengine.h"

StabilityEngine::StabilityEngine()
{
}

void StabilityEngine::setVessel(const Vessel& vessel)
{
    m_vessel = vessel;
}

void StabilityEngine::compute()
{
    m_draft = m_hydrostatics.calculateDraft(m_vessel);
    m_KB = m_hydrostatics.calculateKB(m_vessel);
    m_BM = m_hydrostatics.calculateBM(m_vessel);
    m_KM = m_KB + m_BM;
    m_GM = m_KM - m_vessel.KG();
}

double StabilityEngine::getDraft() const { return m_draft; }
double StabilityEngine::getKB() const { return m_KB; }
double StabilityEngine::getBM() const { return m_BM; }
double StabilityEngine::getKM() const { return m_KM; }
double StabilityEngine::getGM() const { return m_GM; }

QString StabilityEngine::getStabilityCondition() const
{
    if (m_GM > 0.0)
        return "Positive Stability";
    else if (m_GM < 0.0)
        return "Negative Stability";
    else
        return "Neutral Stability";
}
