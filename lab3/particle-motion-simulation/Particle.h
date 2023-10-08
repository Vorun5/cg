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

    // Радиус растицы
    static const float radius;
    // Масса частицы
    static const float mass;
    // Коэффициент силы Кулона
    static const float coulombConstant;
    // Максимальная скорость частицы
    static const float maxSpeed;
    // Ограничиваем силу, чтобы избежать слишком больших значений
    static const float maxForce;

private:
    float m_x, m_y;
    // Коэффиценты усорения частицы
    float m_vx, m_vy;
    // Заряд частицы (<=0 отрицательная, >0 положительная)
    float m_charge;
};