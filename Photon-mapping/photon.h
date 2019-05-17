#ifndef PHOTON_H_
#define PHOTON_H_

#include <impact.h>
#include <types.h>

namespace photonmapping
{

    struct Photon
    {
        Color<Real> power;
        Impact impact;
        uint8_t plane;
    };

} // photonmapping

#endif // PHOTON_H_