#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>

#include <json.h>

#include <impact.h>
#include <light.h>
#include <shape.h>
#include <types.h>

namespace photonmapping
{
    class JsonConfig;

    class Scene
    {
    public:

        Scene() = default;

        Scene(const Scene&) = default;
        Scene& operator=(const Scene&) = default;

        Scene& operator<<(const JsonConfig&);
        const std::vector<Light>& get_lights() const;
        const std::vector<std::shared_ptr<Shape>>& get_shapes() const;

        std::pair<bool, Impact> trace(const Point3D<Real>& origin, const Vector3D<Real>& direction) const;

    private:

        std::vector<Light> lights_;
        std::vector<std::shared_ptr<Shape>> shapes_;
    };

} // namespace photonmapping

#endif // SCENE_H_