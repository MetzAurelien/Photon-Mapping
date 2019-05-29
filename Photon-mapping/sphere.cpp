#include <sphere.h>

namespace photonmapping
{

    Sphere::Sphere(const Color<Real>& color, Real absorption_ratio, Real reflection_ratio, Real refraction_ratio,
        const Point3D<Real>& position, Real radius)
        : Shape(color, absorption_ratio, reflection_ratio, refraction_ratio),
        center_(position), radius_(radius), squared_radius_(radius * radius)
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
        const Vector3D<Real> origin_center = center_ - origin;

        if ((origin_center * direction) > 0 && origin_center.get_squared_norm() > squared_radius_)
        {
            const Vector3D<Real> center_projection = Vector3D<Real>::projection(direction, origin_center) + origin;
            const Real center_projection_center_distance = (center_ - center_projection).get_squared_norm();

            if (center_projection_center_distance > squared_radius_)
            {
                return ImpactDistanceRatio(false, 0);
            }
            else
            {
                const Real distance = std::sqrt(squared_radius_ - center_projection_center_distance);

                if (origin_center.get_squared_norm() > squared_radius_)
                {
                    return ImpactDistanceRatio(true, (center_projection - origin).get_norm() - distance);
                }
                else
                {
                    return ImpactDistanceRatio(true, (center_projection - origin).get_norm() - distance);
                }
            }
        }
        return ImpactDistanceRatio(false, 0);
    }

} // namespace photonmapping