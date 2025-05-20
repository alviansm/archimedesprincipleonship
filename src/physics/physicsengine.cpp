#include "physicsengine.h"

PhysicsEngine::PhysicsEngine()
{
    b2WorldDef def = b2DefaultWorldDef();  // use this, not `{}` or custom
    def.gravity = {0.0f, 9.8f};
    m_worldId = b2CreateWorld(&def);

    // Create ground
    b2BodyDef groundDef = b2DefaultBodyDef();
    groundDef.position = {0.0f, 15.0f};  // higher so we can see fall
    b2BodyId ground = b2CreateBody(m_worldId, &groundDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    b2Polygon groundShape = b2MakeBox(50.0f, 1.0f);
    b2CreatePolygonShape(ground, &shapeDef, &groundShape);
}


// PhysicsEngine::PhysicsEngine()
// {
//     b2WorldDef def = {};
//     def.gravity = {0.0f, 9.8f};

//     m_worldId = b2CreateWorld(&def);

//     // Create static ground
//     b2BodyDef groundDef = b2DefaultBodyDef();
//     // groundDef.position = {5.0f, 15.0f};
//     groundDef.position = {0.0f, 10.0f};


//     b2BodyId ground = b2CreateBody(m_worldId, &groundDef);

//     b2ShapeDef shapeDef = b2DefaultShapeDef();
//     b2Polygon groundBox = b2MakeBox(50.0f, 1.0f);
//     b2CreatePolygonShape(ground, &shapeDef, &groundBox);
// }

void PhysicsEngine::step(float timeStep, int subSteps) {
    b2World_Step(m_worldId, timeStep, subSteps);
    b2Vec2 g = b2World_GetGravity(m_worldId);
    qDebug() << "Gravity:" << g.x << g.y;
    if (!m_dynamicBodies.empty()) {
        b2Vec2 pos = b2Body_GetPosition(m_dynamicBodies[0]);
        qDebug() << "Body y:" << pos.y;
    }
}

void PhysicsEngine::addTestBox() {
    b2BodyDef def = b2DefaultBodyDef();
    def.type = b2_dynamicBody;
    def.position = {10.0f, 5.0f};

    b2BodyId bodyId = b2CreateBody(m_worldId, &def);
    b2Body_SetAwake(bodyId, true);
    b2Body_EnableSleep(bodyId, false);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    shapeDef.material.restitution = 0.1f;

    b2Polygon box = b2MakeBox(1.0f, 1.0f);
    b2CreatePolygonShape(bodyId, &shapeDef, &box);

    m_dynamicBodies.push_back(bodyId);

    float mass = b2Body_GetMass(bodyId);
    qDebug() << "Mass:" << mass;  // Must be > 0
}

std::vector<b2BodyId> PhysicsEngine::dynamicBodies() const {
    return m_dynamicBodies;
}

b2WorldId PhysicsEngine::worldId() const {
    return m_worldId;
}
