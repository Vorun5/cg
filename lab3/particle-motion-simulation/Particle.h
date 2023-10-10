#pragma once
#include <GLFW/glfw3.h>

class Particle {
public:
    Particle(float x, float y, float charge);

    void Update();
    void Render();
    float GetX() const;
    float GetCharge() const;
    float GetY() const;
    float GetVx() const;
    float GetVy() const;
    void SetVelocity(float newVx, float newVy);
    void AddVelocity(float deltaVx, float deltaVy);

    static const float radius;
    static const float mass;
    static const float coulombConstant;
    static const float maxSpeed;
    static const float maxForce;

private:
    float m_x, m_y;
    float m_vx, m_vy;
    float m_charge;
};