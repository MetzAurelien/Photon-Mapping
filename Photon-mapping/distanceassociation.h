#ifndef DISTANCEASSOCIATION_H_
#define DISTANCEASSOCIATION_H_

#include <types.h>

namespace photonmapping
{
    template<typename T>
    class DistanceAssociation
    {
    public:

        DistanceAssociation();
        DistanceAssociation(const T&, Real distance);

        DistanceAssociation(const DistanceAssociation&) = delete;
        DistanceAssociation& operator=(const DistanceAssociation&) = delete;

        DistanceAssociation(DistanceAssociation&&);
        DistanceAssociation& operator=(DistanceAssociation&&);

        const T& get_object() const;
        Real get_distance() const;

    private:

        const T* object_;
        Real distance_;

    };
    template<typename T>
    DistanceAssociation<T>::DistanceAssociation() = default;

    template<typename T>
    DistanceAssociation<T>::DistanceAssociation(const T& object, Real distance)
        : object_(&object), distance_(distance)
    {
    }

    template<typename T>
    DistanceAssociation<T>::DistanceAssociation(DistanceAssociation&& other)
        : object_(other.object_), distance_(other.distance_)
    {
    }
    template<typename T>
    DistanceAssociation<T>& DistanceAssociation<T>::operator=(DistanceAssociation&& other)
    {
        object_ = other.object_;
        distance_ = other.distance_;
        return *this;
    }

    template<typename T>
    const T& DistanceAssociation<T>::get_object() const { return *object_; }
    template<typename T>
    Real DistanceAssociation<T>::get_distance() const { return distance_; }

    template<typename T>
    bool operator<(const DistanceAssociation<T>& lhs, const DistanceAssociation<T>& rhs)
    {
        return lhs.get_distance() < rhs.get_distance();
    }


} // namespace photonmapping

#endif // DISTANCEASSOCIATION_H_