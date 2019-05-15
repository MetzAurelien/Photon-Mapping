#include <light.h>

namespace photonmapping
{
    
    Light::Light(const Point3D<Real>& position, std::size_t power)
        : position_(position), power_(power)
    {
    }

    const Point3D<Real>& Light::get_position() const { return position_; }

    std::size_t Light::get_power() const { return power_; }

} // namespace photonmapping