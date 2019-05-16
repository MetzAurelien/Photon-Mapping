#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>

#include <json.h>

#include <impact.h>
#include <jsonconfig.h>
#include <light.h>
#include <shape.h>

namespace photonmapping
{
    struct Scene
    {

        Scene() = default;

        Scene(const Scene&) = default;
        Scene& operator=(const Scene&) = default;

        std::pair<bool, Impact> trace(const Point3D<Real>& origin, const Vector3D<Real>& direction) const;

        std::vector<Light> lights;
        std::vector<std::shared_ptr<Shape>> shapes;
    };

    Scene& operator<<(Scene&, const JsonConfig&);

} // namespace photonmapping

#endif // SCENE_H_