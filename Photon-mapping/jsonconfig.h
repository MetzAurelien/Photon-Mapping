#ifndef CONFIG_H_
#define CONFIG_H_

#include <iconfig.h>

#include <string>

#include <json.h>

namespace photonmapping
{

    class JsonConfig : public IConfig
    {
    public:
        
        JsonConfig() {}

        JsonConfig(const JsonConfig&) = delete;
        JsonConfig& operator=(const JsonConfig&) = delete;

        void load(const char* filename);

        template<typename T, typename... Args>
        T get(Args... args) const
        {
            return get(config_, args);
        }

    private:

        template<typename... Args>
        const nlohmann::json& get(const nlohmann::json& json, const char* first, Args... args)
        {
            return get(json[first], args...);
        }

        nlohmann::json config_;

    };

} // photonmapping

#endif // CONFIG_H_