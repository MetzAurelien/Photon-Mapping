#ifndef PHOTONMAP_H_
#define PHOTONMAP_H_

#include <photon.h>

namespace photonmapping
{
    template<typename T>
    class DistanceAssociation;
    class JsonConfig;
    class Scene;

    class PhotonMap
    {
    public:

        using SizeType = std::vector<Photon>::size_type;

        PhotonMap();

        PhotonMap& operator<<(const JsonConfig&);

        void emit(const Scene&);

        Color<Real> irradiance_estimate(const Impact&) const;
        
    private:

        void locate_photons(std::vector<DistanceAssociation<Photon>>& result, const Impact& impact, SizeType index) const;

        void balence_segment(SizeType index, SizeType first, SizeType last);

        void photon_bounce(const Scene&, const Impact&, const Vector3D<Real>&);
        void photon_bounce(const Scene&, const Impact&);

        void store(const Impact&);

        static Real zero_one_random();
        
        SizeType research_max_distance_;
        SizeType research_max_squared_distance_;
        SizeType research_max_photons_;

        Real luminosity_;

        std::vector<Photon> photons_;
        std::vector<Photon> tree_;

        SizeType half_photons_number_;

        Point3D<Real> bound_min_;
        Point3D<Real> bound_max_;

    };

} // namespace photonmapping

#endif // PHOTONMAP_H_