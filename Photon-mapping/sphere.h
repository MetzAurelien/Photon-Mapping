#ifndef SPHERE_H_
#define SPHERE_H_

#include <shape.h>

namespace photonmapping
{

    class Sphere : public Shape
    {
    public:

        using Real = Shape::Real;
        using ImpactDistanceRation = Shape::ImpactDistanceRatio;

        Sphere(const Color<Real>&, Real absorption_ratio, Real reflection_ratio, Real refraction_ratio,
            const Point3D<Real>& position, Real radius);

        Sphere(const Sphere&) = default;
        Sphere& operator=(const Sphere&) = default;

        const Point3D<Real>& get_center() const;
        Real get_radius() const;

        virtual void output(std::ostream&) const;

        virtual Vector3D<Real> get_normal(const Point3D<Real>& impact) const;
        virtual ImpactDistanceRatio get_impact_distance_ratio(const Point3D<Real>& origin, const Vector3D<Real>& direction) const;

    private:

        Point3D<Real> center_;
        Real radius_;
    };

} // namespace photonmapping

#endif // SPHERE_H_