#include <rt/lights/pointlight.h>
#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity)
{
    this -> position = position;
    this -> intensity = intensity;
}

LightHit PointLight::getLightHit(const Point& p) const { 
    Vector dir = position - p;
    float distance = dir.length();   
    if (fabs(distance) < epsilon) {
        return LightHit{dir, distance, Vector(0,0,0)};
    }
    return LightHit{dir, distance, dir.normalize()};
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    if (fabs(irr.distance) < epsilon) return intensity;
    return intensity/(irr.distance*irr.distance);
}

}
