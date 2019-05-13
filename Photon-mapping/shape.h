#ifndef SHAPE_H_
#define SHAPE_H_

#include <ostream>

#include <types.h>
#include <vector.h>

namespace photonmapping
{

    class Shape
    {
    public:

        using Real = double;
        using ImpactDistanceRatio = std::pair<bool, Real>;

        Shape(const Color<Real>&, Real absorption_ratio, Real reflectance_ratio, Real refractance_ratio);

        Shape(const Shape&) = default;
        Shape& operator=(const Shape&) = default;

        const Color<Real>& get_color() const;
        Real get_absorption_ratio() const;
        Real get_reflectance_ratio() const;
        Real get_refractance_ratio() const;

        virtual void output(std::ostream&) const = 0;

        virtual Vector3D<Real> get_normal(const Point3D<Real>&) const = 0;
        virtual ImpactDistanceRatio get_impact_distance_ratio(const Point3D<Real>& origin, const Vector3D<Real>& direction) const = 0;

    private:

        Color<Real> color_;
        Real absorption_ratio_;
        Real reflection_ratio_;
        Real refraction_ratio_;

    };

} // photonmapping

#endif // SHAPE_H_
