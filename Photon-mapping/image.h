#ifndef IMAGE_H_
#define IMAGE_H_

#include <mutex>
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

        SizeType get_width() const;
        SizeType get_height() const;

        void set(SizeType x, SizeType y, Pixels::value_type r, Pixels::value_type g, Pixels::value_type b, Pixels::value_type a);

        unsigned int encode() const;

    private:

        enum Composant {
            kRed = 0,
            kBlue = 1,
            kGreen = 2,
            kAlpha = 3,
            kNumber = 4
        };

        std::mutex mutex_;

        std::string filename_;
        SizeType width_;
        SizeType height_;
        Pixels pixels_;

    };

} // namespace photonmapping

#endif // IMAGE_H_