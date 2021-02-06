#ifndef H_RAYTRACING_PUNCTUAL_H
#define H_RAYTRACING_PUNCTUAL_H

#include "Light.h"

/**
 * @class Punctual
 * @brief Class that manage the punctual light.
 *
 * This class provides information about the punctual light (origin).
 *
 * @see Vector3, Matrix, Light
 */
class Punctual : public Light
{
public:
    /**
     * @brief Constructor to initialize a punctual light.
     *
     * @param intensity The intensity of the light
     * @param origin   The origin of the light
     */
    Punctual(double intensity, Vector3 origin);

    /*
     * @brief Method that return if intersection is enlightened.
     *
     * @param intersection The secondary ray
     *
     * @return Returns true if the intersection is enlightened.
     */
    bool isEnLight(Ray intersection) override;

    /**
     * @brief Method to get the origin of the light.
     *
     * @param intersection The secondary ray
     *
     * @return Returns the origin point of the light.
     */
    std::optional<Vector3> getOrigin(Ray intersection) override;

    /**
     * @brief Method to get the direction of the light.
     *
     * @param intersection The secondary ray
     *
     * @return Returns the direction of the light.
     */
    std::optional<Vector3> getDirection(Ray intersection) override;

private:
    /**
     * The origin of the light.
     */
    Vector3 m_origin;
};

#endif //H_RAYTRACING_PUNCTUAL_H
