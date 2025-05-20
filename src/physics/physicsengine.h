#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#pragma once

#include <QDebug>

#include <box2d/box2d.h>
#include <vector>

class PhysicsEngine {
public:
    PhysicsEngine();
    void step(float timeStep = 1.0f / 60.0f, int subStepCount = 4);

    void addTestBox();

    std::vector<b2BodyId> dynamicBodies() const;
    b2WorldId worldId() const;

private:
    b2WorldId m_worldId;
    std::vector<b2BodyId> m_dynamicBodies;
};

#endif // PHYSICSENGINE_H
