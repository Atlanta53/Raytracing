#include "Directional.h"

#include <utility>

Directional::Directional(double intensity, Vector3 originA, Vector3 originB, Vector3 direction)
    : Light(intensity),
      m_originA(std::move(originA)),
      m_originB(std::move(originB)),
      m_direction(std::move(direction))
{
}

bool Directional::isEnLight(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return false;

    Vector3 ab = m_originB - m_originA;

    const Vector3& origin = intersection.getOrigin();
    const Vector3& direction = intersection.getDirection() * -1;

    double den = ab.x() * direction.y() - ab.y() * direction.x();

    // Verify if the vector aren't parallel
    if (den == 0)
        return false;

    double x = -((m_originA.x() - origin.x()) * direction.y() - (m_originA.y() - origin.y()) * direction.x()) / den;

    double m = -((origin.y() - m_originA.y()) * ab.x() - (origin.x() - m_originA.x()) * ab.y()) / den;

    // Verify if it is in the range of originA and originB
    if (x < 0 || x > 1)
        return false;

    // 3D validation
    if (ab.z() * x + m_originA.z() != origin.z() + direction.z() * m)
        return false;

    // Verify if the direction have the same orientation
    if ((m_direction.x() != 0 && (origin - m_direction).toVector3().x() / m_direction.x() < 0) ||
        (m_direction.y() != 0 && (origin - m_direction).toVector3().y() / m_direction.y() < 0) ||
        (m_direction.z() != 0 && (origin - m_direction).toVector3().z() / m_direction.z() < 0))
        return false;

    return true;
}

std::optional<Vector3> Directional::getOrigin(Ray intersection)
{
    if (intersection.getType() != SECONDARY)
        return std::nullopt;

    Vector3 ab = m_originB - m_originA;

    const Vector3& origin = intersection.getOrigin();
    const Vector3& direction = intersection.getDirection() * -1;

    double den = ab.x() * direction.y() - ab.y() * direction.x();

    // Verify if the vector aren't parallel
    if (den == 0)
        return std::nullopt;

    double x = -((m_originA.x() - origin.x()) * direction.y() - (m_originA.y() - origin.y()) * direction.x()) / den;

    double m = -((origin.y() - m_originA.y()) * ab.x() - (origin.x() - m_originA.x()) * ab.y()) / den;

    // Verify if it is in the range of originA and originB
    if (x < 0 || x > 1)
        return std::nullopt;

    // 3D validation
    if (ab.z() * x + m_originA.z() != origin.z() + direction.z() * m)
        return std::nullopt;

    // Verify if the direction have the same orientation
    if ((m_direction.x() != 0 && (origin - m_direction).toVector3().x() / m_direction.x() < 0) ||
        (m_direction.y() != 0 && (origin - m_direction).toVector3().y() / m_direction.y() < 0) ||
        (m_direction.z() != 0 && (origin - m_direction).toVector3().z() / m_direction.z() < 0))
        return std::nullopt;

    return direction * m + origin;
}

std::optional<Vector3> Directional::getDirection(Ray intersection)
{
    return m_direction - intersection.getOrigin();
}
