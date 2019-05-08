#include <image.h>

namespace photonmapping
{

    Image::Image(const std::string& filename, Pixels::size_type width, Pixels::size_type height)
        : filename_(filename), width_(width), height_(height), pixels_(width_ * height_ * kPixelSize) 
    {
    }

} // photonmapping