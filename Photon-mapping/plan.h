#ifndef PLAN_H_
#define PLAN_H_

#include <shape.h>

namespace photonmapping
{

    class Plan : public Shape
    {
    public:

        using Real = Shape::Real;
        using ImpactDistanceRation = Shape::ImpactDistanceRatio;

        Plan(const Color<Real>&, Real absorption_ratio, Real reflection_ratio, Real refraction_ratio,
            const Point3D<Real>& position, const Vector3D<Real>& normal);

        const Point3D<Real>& get_position() const;

        virtual void output(std::ostream&) const;

        virtual Vector3D<Real> get_normal(const Point3D<Real>&) const;
        virtual ImpactDistanceRatio get_impact_distance_ratio(const Point3D<Real>& origin, const Vector3D<Real>& direction) const;

    private:

        Point3D<Real> position_;
        Vector3D<Real> normal_;
    };

} // namespace photonmapping

#endif // PLAN_H_