#ifndef HYDROSTATICS_H
#define HYDROSTATICS_H

#include "vessel.h"

class Hydrostatics
{
public:
    Hydrostatics();

    double calculateDraft(const Vessel& vessel) const;
    double calculateKB(const Vessel& vessel) const;
    double calculateBM(const Vessel& vessel) const;

private:
    double calculateDisplacedVolume(const Vessel& vessel) const;
};

#endif // HYDROSTATICS_H
