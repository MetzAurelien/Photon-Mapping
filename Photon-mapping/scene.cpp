#include <scene.h>

#include <algorithm>

#include <distanceassociation.h>
#include <jsonconfig.h>
#include <plan.h>
#include <sphere.h>
#include <triangle.h>

namespace photonmapping
{

    const std::vector<Light>& Scene::get_lights() const { return lights_; }
    const std::vector<std::shared_ptr<Shape>>& Scene::get_shapes() const { return shapes_; }

    std::pair<bool, Impact> Scene::trace(const Point3D<Real>& origin, const Vector3D<Real>& direction) const
    {
        std::vector<DistanceAssociation<std::shared_ptr<Shape>>> distances;
        
        for (const std::shared_ptr<Shape>& shape : shapes_)
        {
            auto[impact, distance] = shape->get_impact_distance_ratio(origin, direction);
            if (impact)
                distances.push_back(DistanceAssociation<std::shared_ptr<Shape>>(shape, distance));
        }

        if (distances.empty() == false)
        {
            auto min_element = std::min_element(distances.cbegin(), distances.cend());

            Impact impact;

            impact.position = Vector3D<Real>::distance_ratio_to_point(origin, direction, min_element->get_distance());
            impact.direction = -direction;
            impact.shape = min_element->get_object();
            impact.normal = min_element->get_object()->get_normal(impact.position);
            impact.scalar = impact.direction * impact.normal;

            return std::make_pair(true, impact);
        }

        return std::make_pair(false, Impact());
    }

    Scene& Scene::operator<<(const JsonConfig& json_config)
    {
        nlohmann::json shapes = json_config.get<nlohmann::json>("Scene", "Shapes");
        nlohmann::json lights = json_config.get<nlohmann::json>("Scene", "Lights");

        for (const auto&[key, value] : lights.items())
            lights_.push_back(Light(
                Point3D<Real>(value["position"]["x"], value["position"]["y"], value["position"]["z"]),
                value["power"]
            ));
        for (const auto&[key, value] : shapes.items())
        {
            Color<Real> color = { value["color"]["r"], value["color"]["g"], value["color"]["b"] };
            if (value["name"] == "sphere")
            {
                shapes_.push_back(std::make_shared<Sphere>(
                    color, value["absorption_ratio"], value["reflection_ratio"], value["refraction_ratio"],
                    Point3D<Real>(value["position"]["x"], value["position"]["y"], value["position"]["z"]),
                    value["radius"]
                    ));
            }
            else if (value["name"] == "triangle")
            {
                shapes_.push_back(std::make_shared<Triangle>(
                    color, value["absorption_ratio"], value["reflection_ratio"], value["refraction_ratio"],
                    Point3D<Real>(value["a"]["x"], value["a"]["y"], value["a"]["z"]),
                    Point3D<Real>(value["b"]["x"], value["b"]["y"], value["b"]["z"]),
                    Point3D<Real>(value["c"]["x"], value["c"]["y"], value["c"]["z"])
                    ));
            }
            else if (value["name"] == "plan")
            {
                shapes_.push_back(std::make_shared<Plan>(
                    color, value["absorption_ratio"], value["reflection_ratio"], value["refraction_ratio"],
                    Point3D<Real>(value["position"]["x"], value["position"]["y"], value["position"]["z"]),
                    Vector3D<Real>(value["normal"]["x"], value["normal"]["y"], value["normal"]["z"])
                    ));
            }
        }
        return *this;
    }

} // namespace photonmapping