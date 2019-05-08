#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include <vector>

namespace photonmapping
{

    class Image
    {
    public:

        using Pixels = std::vector<unsigned char>;

        static constexpr Pixels::size_type kPixelSize = 4;

        Image(const std::string& filename, Pixels::size_type width, Pixels::size_type height);

        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

    private:

        std::string filename_;
        Pixels::size_type width_;
        Pixels::size_type height_;
        Pixels pixels_;

    };

} // namespace photonmapping

#endif // IMAGE_H_