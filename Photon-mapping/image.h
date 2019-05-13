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
        using SizeType = Pixels::size_type;

        static constexpr Pixels::size_type kPixelSize = 4;

        Image(const std::string& filename, SizeType width, SizeType height);

        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

    private:

        std::string filename_;
        SizeType width_;
        SizeType height_;
        Pixels pixels_;

    };

} // namespace photonmapping

#endif // IMAGE_H_