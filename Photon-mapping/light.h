#ifndef LIGHT_H_
#define LIGHT_H_

#include <types.h>
#include <vector.h>

namespace photonmapping
{

    class Light {

    public:
        
        Light(const Point3D<Real>& position, std::size_t power);

        Light(const Light&) = default;
        Light& operator=(const Light&) = default;

        const Point3D<Real>& get_position() const;
        std::size_t get_power() const;

    private:

        Point3D<Real> position_;
        std::size_t power_;

    };

} // namespace photonmapping

#endif // LIGHT_H_