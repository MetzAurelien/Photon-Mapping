#include <jsonconfig.h>

#include <fstream>

namespace photonmapping
{

    void JsonConfig::load(const char* filename)
    {
        std::ifstream ifs(filename);
        ifs >> config_;
    }

} // namespace photonmapping