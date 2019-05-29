#include <exception>
#include <iostream>
#include <thread>

#include <image.h>
#include <jsonconfig.h>
#include <photonmap.h>
#include <raytracerslave.h>
#include <scene.h>
#include <types.h>

namespace photonmapping
{
    void raytracer(Image& image, const Scene& scene, const PhotonMap& photon_map, const JsonConfig& json_config)
    {
        const std::size_t threads_num = std::max(std::thread::hardware_concurrency(), 2u);
        const Image::SizeType package_size = image.get_height() / threads_num;
        std::vector<std::thread> threads;
        RayTracerSlave slave(image, scene, json_config, photon_map);

        Image::SizeType offset = 0;
        for (std::size_t index = 0; index < threads_num; ++index)
        {
            threads.push_back(std::thread(slave, offset, offset + package_size));
            offset += package_size;
        }
        if (offset < image.get_height())
        {
            slave(offset, image.get_height());
        }

        for (std::thread& thread : threads) thread.join();
    }
}

int main()
{
    try
    {
        photonmapping::JsonConfig config;
        config.load("Simulation.json");

        photonmapping::Image image(
            config.get<std::string>("Image", "filename"),
            config.get<photonmapping::Image::SizeType>("Image", "width"),
            config.get<photonmapping::Image::SizeType>("Image", "height")
        );

        photonmapping::Scene scene;
        scene << config;

        photonmapping::PhotonMap photon_map;
        photon_map << config;
        photon_map.emit(scene);

        photonmapping::raytracer(image, scene, photon_map, config);

        image.encode();
    }

    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::string s;
        std::cin >> s;
        return photonmapping::kFailure;
    }

    return photonmapping::kSuccess;
}