#ifndef IMPACT_H_
#define IMPACT_H_

#include <memory>

#include <types.h>
#include <vector.h>

namespace photonmapping
{
    class Shape;

    struct Impact
    {
        std::shared_ptr<Shape> shape;

        Vector3D<Real> direction;
        Vector3D<Real> normal;
        Point3D<Real> position;
        Real scalar;
    };

} // namespace photonmapping

#endif // IMPACT_H_