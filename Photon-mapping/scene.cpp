#include <scene.h>

#include <algorithm>

#include <sphere.h>
#include <plan.h>
#include <triangle.h>

namespace photonmapping
{

    std::pair<bool, Impact> Scene::trace(const Point3D<Real>& origin, const Vector3D<Real>& direction)
    {
        using Distance = std::pair<const std::shared_ptr<Shape>&, Real>;

        std::unordered_map<const std::shared_ptr<Shape>&, Real> distances;
        
        for (const auto& shape : shapes)
        {
            auto[impact, distance] = shape->get_impact_distance_ratio(origin, direction);
            if (impact) distances[shape] = distance;
        }

        if (distances.empty() == false)
        {
            auto min_element = std::min_element(distances.cbegin(), distances.cend(),
                [](const decltype(distances)::value_type& lhs, const decltype(distances)::value_type& rhs)
            {
                return lhs < rhs;
            });

            const std::shared_ptr<Shape>& shape = min_element->first;
            Real distance = min_element->second;

            Impact impact;

            impact.position = Vector3D<Real>::distance_ratio_to_point(origin, direction, distance);
            impact.direction = -direction;
            impact.shape = shape;
            impact.normal = shape->get_normal(impact.position);
            impact.scalar = impact.direction * impact.normal;

            return std::make_pair(true, impact);
        }

        return std::make_pair(false, Impact());
    }

    Scene& operator<<(Scene& scene, const JsonConfig& json_config)
    {
        nlohmann::json shapes = json_config.get<nlohmann::json>("Scene", "Shapes");
        nlohmann::json lights = json_config.get<nlohmann::json>("Scene", "Lights");

        for (const auto&[key, value] : lights.items())
            scene.lights.push_back(Light(
                Point3D<Real>(value["position"]["x"], value["position"]["y"], value["position"]["z"]),
                value["power"]
            ));
        for (const auto&[key, value] : shapes.items())
        {
            Color<Real> color = { value["color"]["r"], value["color"]["g"], value["color"]["b"] };
            if (value["name"] == "sphere")
            {
                scene.shapes.push_back(std::make_shared<Sphere>(
                    color, value["absorption_ratio"], value["relfection_ratio"], value["refraction_ratio"],
                    Point3D<Real>(value["position"]["x"], value["position"]["y"], value["position"]["z"]),
                    value["radius"]
                    ));
            }
            else if (value["name"] == "triangle")
            {
                scene.shapes.push_back(std::make_shared<Triangle>(
                    color, value["absorption_ratio"], value["relfection_ratio"], value["refraction_ratio"],
                    Point3D<Real>(value["a"]["x"], value["a"]["y"], value["a"]["z"]),
                    Point3D<Real>(value["b"]["x"], value["b"]["y"], value["b"]["z"]),
                    Point3D<Real>(value["c"]["x"], value["c"]["y"], value["c"]["z"])
                    ));
            }
            else if (value["name"] == "plan")
            {
                scene.shapes.push_back(std::make_shared<Plan>(
                    color, value["absorption_ratio"], value["relfection_ratio"], value["refraction_ratio"],
                    Point3D<Real>(value["position"]["x"], value["position"]["y"], value["position"]["z"]),
                    Vector3D<Real>(value["normal"]["x"], value["normal"]["y"], value["normal"]["z"])
                    ));
            }
        }
        return scene;
    }

} // namespace photonmapping