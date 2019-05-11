#include <sphere.h>

namespace photonmapping
{
    using Real = Sphere::Real;
    using ImpactDistanceRatio = Sphere::ImpactDistanceRatio;
    
    Sphere::Sphere(const Color<Real>& color, Real absorption_ratio, Real reflection_ratio, Real refraction_ratio,
        const Point3D<Real>& position, Real radius)
        : Shape(color, absorption_ratio, reflection_ratio, refraction_ratio), center_(position), radius_(radius)
    {
    }

    const Vector3D<Real>& Sphere::get_center() const { return center_; }
    Real Sphere::get_radius() const { return radius_; }

    void Sphere::output(std::ostream& os) const
    {
        os << "Sphere : {" << std::endl;
        os << "    center : " << center_ << std::endl;
        os << "    radius : " << radius_ << std::endl;
        os << "}" << std::endl;
    }

    Vector3D<Real> Sphere::get_normal(const Point3D<Real>& impact) const
    {
        return (impact - center_).get_normalized();
    }

    ImpactDistanceRatio Sphere::get_impact_distance_ratio(const Point3D<Real>& origin, const Vector3D<Real>& direction) const
    {
        const Vector3D<Real> origin_to_center = center_ - origin;
        const Real origin_to_center_scalar_direction = origin_to_center * direction;

        const Real discriminant = std::pow(origin_to_center_scalar_direction, 2) -
            (origin_to_center * origin_to_center) + std::pow(radius_, 2);

        if (discriminant >= 0)
        {
            const std::array<Real, 2> solutions = 
            {
                origin_to_center_scalar_direction + std::sqrt(discriminant),
                origin_to_center_scalar_direction - std::sqrt(discriminant)
            };

            for (Real solution : solutions)
                if (solution > 0) return ImpactDistanceRatio(true, solution);
        }

        return ImpactDistanceRatio(false, 0);
    }

} // namespace photonmapping