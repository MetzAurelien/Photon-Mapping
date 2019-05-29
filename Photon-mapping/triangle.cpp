#include <triangle.h>

namespace photonmapping
{

    Triangle::Triangle(const Color<Real>& color, Real absorption_ratio, Real reflection_ratio, Real refraction_ratio,
        const Point3D<Real>& a, const Point3D<Real>& b, const Point3D<Real>& c)
        : Shape(color, absorption_ratio, reflection_ratio, refraction_ratio), a_(a), b_(b), c_(c),
          normal_(((b_ - a_) ^ (c_ - a_)).get_normalized())
    {
    }

    const Point3D<Real>& Triangle::get_a() const { return a_; }
    const Point3D<Real>& Triangle::get_b() const { return b_; }
    const Point3D<Real>& Triangle::get_c() const { return c_; }

    void Triangle::output(std::ostream& os) const
    {
        os << "Triangle {" << std::endl;
        os << "    a : " << a_ << "," << std::endl;
        os << "    b : " << b_ << "," << std::endl;
        os << "    c : " << c_ << "," << std::endl;
        os << "}" << std::endl;
    }

    Vector3D<Real> Triangle::get_normal(const Point3D<Real>&) const { return normal_; }

    ImpactDistanceRatio Triangle::get_impact_distance_ratio(const Point3D<Real>& origin, const Vector3D<Real>& direction) const
    {
        if (-direction * normal_ <= 0) return ImpactDistanceRatio(false, 0);

        Real dist = ((a_ - origin) * normal_) / (direction * normal_);

        Point3D<Real> intersection = Vector3D<Real>::distance_ratio_to_point(origin, direction, dist);

        std::array<Vector3D<Real>, 3> heights = {
            (b_ - a_) - Vector3D<Real>::projection(b_ - c_, b_ - a_),
            (c_ - b_) - Vector3D<Real>::projection(c_ - a_, c_ - b_),
            (a_ - c_) - Vector3D<Real>::projection(a_ - b_, a_ - c_)
        };
        std::array<Real, 3> barycentrics = {
            1 - (heights[0] * (intersection - a_) / (heights[0] * (b_ - a_))),
            1 - (heights[1] * (intersection - b_) / (heights[1] * (c_ - b_))),
            1 - (heights[2] * (intersection - c_) / (heights[2] * (a_ - c_)))
        };

        if (barycentrics[0] < 0 || barycentrics[1] < 0 || barycentrics[2] < 0)
            return ImpactDistanceRatio(false, 0);

        return ImpactDistanceRatio(true, dist);
    }

} // namespace photonmapping