#ifndef RAYTRACERSLAVE_H_
#define RAYTRACERSLAVE_H_

#include <image.h>

namespace photonmapping
{
    class Scene;
    class JsonConfig;
    class PhotonMap;

    class RayTracerSlave
    {
    public:
        
        RayTracerSlave(Image&, const Scene&, const JsonConfig&, const PhotonMap&);

        RayTracerSlave(const RayTracerSlave&);
        RayTracerSlave& operator=(const RayTracerSlave&);

        RayTracerSlave(RayTracerSlave&&);

        void operator()(Image::SizeType package_begin, Image::SizeType package_size);

    private:

        Image* image_;
        const Scene* scene_;
        const JsonConfig* config_;
        const PhotonMap* photon_map_;
    };

} // namespace photonmapping

#endif // RAYTRACERSLAVE_H_