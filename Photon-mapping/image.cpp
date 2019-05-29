#include <image.h>

#include <lodepng.h>

namespace photonmapping
{

    Image::Image(const std::string& filename, Pixels::size_type width, Pixels::size_type height)
        : filename_(filename), width_(width), height_(height), pixels_(width_ * height_ * kPixelSize) 
    {
    }

    Image::SizeType Image::get_width() const { return width_; }
    Image::SizeType Image::get_height() const { return height_; }

    void Image::set(SizeType x, SizeType y, Pixels::value_type r, Pixels::value_type g, Pixels::value_type b, Pixels::value_type a)
    {
        std::lock_guard lock(mutex_);
        const SizeType offset = Composant::kNumber * width_ * y + Composant::kNumber * x;
        pixels_[offset + Composant::kRed] = r;
        pixels_[offset + Composant::kGreen] = g;
        pixels_[offset + Composant::kBlue] = b;
        pixels_[offset + Composant::kAlpha] = a;
    }

    unsigned int Image::encode() const
    {
        return lodepng::encode(filename_, pixels_, width_, height_);
    }
} // photonmapping