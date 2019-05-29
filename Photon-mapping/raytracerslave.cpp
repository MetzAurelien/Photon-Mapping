#include <raytracerslave.h>

#include <jsonconfig.h>
#include <photonmap.h>
#include <scene.h>
#include <types.h>
#include <vector.h>

namespace photonmapping
{
    std::mutex mutex;
    Real completion = 0;

    RayTracerSlave::RayTracerSlave(Image& image, const Scene& scene, const JsonConfig& config, const PhotonMap& photon_map)
        : scene_(&scene), image_(&image), config_(&config), photon_map_(&photon_map)
    {
    }
    RayTracerSlave::RayTracerSlave(const RayTracerSlave& other)
    {
        scene_ = other.scene_;
        image_ = other.image_;
        config_ = other.config_;
        photon_map_ = other.photon_map_;
    }
    RayTracerSlave::RayTracerSlave(RayTracerSlave&& other)
        : scene_(other.scene_), image_(other.image_), config_(other.config_), photon_map_(other.photon_map_)
    {
    }

    void RayTracerSlave::operator()(Image::SizeType package_begin, Image::SizeType package_end)
    {
        const Real half_image_width = image_->get_width() >> 1;
        const Real half_image_height = image_->get_height() >> 1;
        const Real focal = config_->get<Real>("Simulation", "focal");

        const Real step = (100.0 / static_cast<Real>(package_end - package_begin)) / std::max(std::thread::hardware_concurrency(), 2u);
        
        const Point3D<Real> origin(0.0, 0.0, 0.0);
        Vector3D<Real> direction;

        for (Image::SizeType y = package_begin; y < package_end; ++y)
        {
            for (Image::SizeType x = 0; x < image_->get_width(); ++x)
            {
                direction.set(x - half_image_width, half_image_height - y, focal);
                direction.normalize();
                Color<Real> pixel_color{ 0.0, 0.0, 0.0 };

                if (auto[hit, impact] = scene_->trace(origin, direction); hit)
                {
                    pixel_color = photon_map_->irradiance_estimate(impact);
                    for (Real& composant : pixel_color)
                        composant = std::clamp(composant * impact.scalar, static_cast<Real>(0), static_cast<Real>(255));
                }
                image_->set(x, y, pixel_color[0], pixel_color[1], pixel_color[2], 255);
            }
            {
                std::lock_guard lock(mutex);
                completion += step;
                std::cout << "\rcompletion : " << completion << "%    " << std::flush;
            }
        }
    }

} // namespace photonmapping