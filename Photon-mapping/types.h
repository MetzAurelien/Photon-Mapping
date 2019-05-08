#ifndef TYPES_H_
#define TYPES_H_

namespace photonmapping
{

    enum Status
    {
        kSuccess = 0,
        kFailure = 1
    };

    template<typename T>
    using Color = std::array<T, 3>;

} // namespace photonmapping

#endif // TYPES_H_