#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <shape.h>

namespace photonmapping
{

    class Triangle : public Shape
    {
    public:

        using Real = Shape::Real;
        using ImpactDistanceRation = Shape::ImpactDistanceRatio;

        Triangle(const Color<Real>&, Real absorption_ratio, Real reflection_ratio, Real refraction_ratio,
            const Point3D<Real>&, const Point3D<Real>&, const Point3D<Real>&);
        
        Triangle(const Triangle&) = default;
        Triangle& operator=(const Triangle&) = default;

        const Point3D<Real>& get_a() const;
        const Point3D<Real>& get_b() const;
        const Point3D<Real>& get_c() const;

        virtual void output(std::ostream&) const;

        virtual Vector3D<Real> get_normal(const Point3D<Real>&) const;
        virtual ImpactDistanceRatio get_impact_distance_ratio(const Point3D<Real>& origin, const Vector3D<Real>& direction) const;

    private:

        Point3D<Real> a_;
        Point3D<Real> b_;
        Point3D<Real> c_;
        Vector3D<Real> normal_;

    };

} // namespace photonmapping

#endif // TRIANGLE_H_