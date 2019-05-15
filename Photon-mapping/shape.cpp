#include <shape.h>

namespace photonmapping
{

    Shape::Shape(const Color<Real>& color, Real absorption_ratio, Real reflection_ratio, Real refraction_ratio_)
        : color_(color),
          absorption_ratio_(absorption_ratio / 100),
          reflection_ratio_(absorption_ratio_ + (reflection_ratio / 100)),
          refraction_ratio_(reflection_ratio_ + (refraction_ratio_ / 100))
    {
    }

    const Color<Real>& Shape::get_color() const { return color_; }
    Real Shape::get_absorption_ratio() const { return absorption_ratio_; }
    Real Shape::get_reflectance_ratio() const { return reflection_ratio_; }
    Real Shape::get_refractance_ratio() const { return refraction_ratio_; }

} // photonmapping