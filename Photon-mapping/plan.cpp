#include <plan.h>

namespace photonmapping
{
    using Real = Plan::Real;
    using ImpactDistanceRatio = Plan::ImpactDistanceRatio;

    Plan::Plan(const Color<Real>& color, Real absorption_ratio, Real reflection_ratio, Real refraction_ratio,
        const Point3D<Real>& position, const Vector3D<Real>& normal)
        : Shape(color, absorption_ratio, reflection_ratio, refraction_ratio),
          position_(position), normal_(normal)
    {
    }

    const Point3D<Real>& Plan::get_position() const { return position_; }

    void Plan::output(std::ostream& os) const
    {
        os << "Plan : {" << std::endl;
        os << "    position : " << position_ << "," << std::endl;
        os << "    normal : " << normal_ << "," << std::endl;
        os << "}" << std::endl;
    }

    Vector3D<Real> Plan::get_normal(const Point3D<Real>&) const { return normal_; }

    ImpactDistanceRatio Plan::get_impact_distance_ratio(const Point3D<Real>& origin, const Vector3D<Real>& direction) const
    {
        if (-direction * normal_ <= 0)
        {
            return ImpactDistanceRatio(false, 0);
        }

        return ImpactDistanceRatio(true, ((position_ - origin) * normal_) / (direction * normal_));
    }

} // namespace photonmapping