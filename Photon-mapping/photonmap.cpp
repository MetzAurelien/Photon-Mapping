#include <photonmap.h>

#define _USE_MATH_DEFINES

#include <math.h>

#include <distanceassociation.h>
#include <jsonconfig.h>
#include <scene.h>

namespace photonmapping
{
    PhotonMap::PhotonMap() = default;

    PhotonMap& PhotonMap::operator<<(const JsonConfig& json_config)
    {
        luminosity_ = json_config.get<Real>("Simulation", "Photon_map", "luminosity");
        research_max_photons_ = json_config.get<SizeType>("Simulation", "Photon_map", "reaserch_max_photons");
        research_max_distance_ = json_config.get<SizeType>("Simulation", "Photon_map", "reaserch_max_distance");
        research_max_squared_distance_ = research_max_distance_ * research_max_distance_;

        return *this;
    }

    void PhotonMap::emit(const Scene& scene) 
    {
        for (const Light& light : scene.get_lights())
            for (std::size_t index = 0; index < light.get_power(); ++index)
            {
                Vector3D<Real> direction;
                direction.randomize();

                if (auto[hit, impact] = scene.trace(light.get_position(), direction); hit)
                {
                    store(impact);
                    photon_bounce(scene, impact);
                }
            }

        half_photons_number_ = photons_.size() >> 1;;

        tree_.resize(photons_.size());
        if (photons_.size() > 1) balence_segment(1, 1, photons_.size() - 1);
    }

    Color<Real> PhotonMap::irradiance_estimate(const Impact& impact) const
    {
        std::vector<DistanceAssociation<Photon>> located_photons;
        locate_photons(located_photons, impact, 1);

        if (located_photons.empty()) return { 0.0, 0.0, 0.0 };

        std::sort(located_photons.begin(), located_photons.end());

        if (located_photons.size() > research_max_photons_)
            located_photons.resize(research_max_photons_);

        Color<Real> color = { 0.0, 0.0, 0.0 };

        for (const DistanceAssociation<Photon>& located_photon : located_photons)
        {
            const Photon& photon = located_photon.get_object();

            if (photon.impact.scalar <= 0) continue;

            for (Color<Real>::size_type index = 0; index < color.size(); ++index)
                color[index] += photon.power[index] * photon.impact.scalar;
        }

        const Real density = M_PI * std::sqrt(located_photons.back().get_distance()) * research_max_distance_ /
            static_cast<Real>(research_max_photons_ * 255);

        for (Real& composant : color) composant /= located_photons.size();

        return color;
    }

    void PhotonMap::locate_photons(std::vector<DistanceAssociation<Photon>>& result, const Impact& impact, SizeType index) const
    {
        if (photons_.size() <= 1) return;

        const Photon& median = tree_[index];
        const uint8_t axis = median.plane;
        const Real distance_to_plane = (impact.position.get(axis) - median.impact.position.get(axis));
        const bool overlap = distance_to_plane < research_max_distance_;

        if (index < half_photons_number_)
        {
            if (distance_to_plane > 0)
            {
                locate_photons(result, impact, 2 * index + 1);
                if (overlap)
                    locate_photons(result, impact, 2 * index);
            }
            else
            {
                locate_photons(result, impact, 2 * index);
                if (overlap)
                    locate_photons(result, impact, 2 * index + 1);
            }
        }
        if (overlap && impact.shape == median.impact.shape)
        {
            const Real distance_to_photon = (impact.position - median.impact.position).get_squared_norm();
            if (distance_to_photon <= research_max_squared_distance_)
            {
                result.push_back(DistanceAssociation<Photon>(median, distance_to_photon));
            }
        }
    }

    void PhotonMap::photon_bounce(const Scene& scene, const Impact& impact, const Vector3D<Real>& direction)
    {
        if (auto[hit, new_impact] = scene.trace(impact.position, direction); hit)
        {
            Real pick = zero_one_random();

            if (pick < impact.shape->get_absorption_ratio()) return;

            store(impact);

            if (pick < impact.shape->get_reflectance_ratio())
            {
            }
            else if (pick < impact.shape->get_refractance_ratio())
            {
            }
            else
            {
                photon_bounce(scene, new_impact);
            }
        }
    }
    void PhotonMap::photon_bounce(const Scene& scene, const Impact& impact)
    {
        
        Vector3D<Real> direction;
        direction.randomize();
        if (direction * impact.normal < 0) direction = -direction;
        
        photon_bounce(scene, impact, direction);
    }

    void PhotonMap::balence_segment(SizeType index, SizeType first, SizeType last)
    {
        SizeType median = 1;
        SizeType length = last - first + 1;

        while (4 * median <= length) median += median;
        if (3 * median <= length)
        {
            median += median + first - 1;
        }
        else
        {
            median = last - median + 1;
        }

        Vector3D<Real> bounds_length = bound_max_ - bound_min_;

        uint8_t axis = 2;
        if (bounds_length.get_x() > bounds_length.get_y() &&
            bounds_length.get_x() > bounds_length.get_z())
        {
            axis = 0;
        }
        else if (bounds_length.get_y() > bounds_length.get_z())
        {
            axis = 1;
        }

        std::sort(photons_.begin() + first, photons_.begin() + last, [axis](const Photon& lhs, const Photon& rhs)
        {
            return lhs.impact.position.get(axis) < rhs.impact.position.get(axis);
        });

        tree_[index] = photons_[median];
        tree_[index].plane = axis;

        if (median > first)
        {
            if (first < median - 1)
            {
                Real max = bound_max_.get(axis);
                bound_max_.set(axis, tree_[index].impact.position.get(axis));
                balence_segment(2 * index, first, median - 1);
                bound_max_.set(axis, max);
            }
            else
            {
                tree_[2 * index] = photons_[first];
            }
        }
        if (median < last)
        {
            if (median + 1 < last)
            {
                Real min = bound_min_.get(axis);
                bound_min_.set(axis, tree_[index].impact.position.get(axis));
                balence_segment(2 * index + 1, median + 1, last);
                bound_min_.set(axis, min);
            }
            else
            {
                tree_[2 * index + 1] = photons_[last];
            }
        }
    }

    void PhotonMap::store(const Impact& impact)
    {
        Photon photon;

        if (photons_.empty())
        {
            bound_min_ = impact.position;
            bound_max_ = impact.position;
        }
        else
        {
            for (uint8_t axis = 0; axis < 3; ++axis)
            {
                if (impact.position.get(axis) < bound_min_.get(axis))
                {
                    bound_min_.set(axis, impact.position.get(axis));
                }
                else if (impact.position.get(axis) > bound_max_.get(axis))
                {
                    bound_max_.set(axis, impact.position.get(axis));
                }
            }
        }

        photon.impact = impact;
        photon.power = impact.shape->get_color();

        photons_.push_back(photon);
    }

    Real PhotonMap::zero_one_random()
    {
        std::random_device random;
        std::mt19937 generator(random());
        const std::uniform_real_distribution<> zero_one_distribution(0, 1);

        return zero_one_distribution(generator);
    }

} // namespace photonmapping