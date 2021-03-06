#ifndef TYPES_H_
#define TYPES_H_

#include <array>

namespace photonmapping
{

    enum Status
    {
        kSuccess = 0,
        kFailure = 1
    };

    using Real = double;
    using ImpactDistanceRatio = std::pair<bool, Real>;

    template<typename T>
    using Color = std::array<T, 3>;

} // namespace photonmapping

#endif // TYPES_H_