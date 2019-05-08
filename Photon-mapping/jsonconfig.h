#ifndef CONFIG_H_
#define CONFIG_H_


#include <string>

#include <json.h>

namespace photonmapping
{

    class JsonConfig
    {
    public:
        
        JsonConfig() {}

        JsonConfig(const JsonConfig&) = delete;
        JsonConfig& operator=(const JsonConfig&) = delete;

        void load(const char* filename);

        template<typename T, typename... Args>
        T get(Args... args) const;

    private:

        template<typename T>
        T get(const nlohmann::json&, const char* name) const;

        template<typename T, typename... Args>
        T get(const nlohmann::json&, const char* first, Args...) const;

        nlohmann::json config_;

    };

    template<typename T, typename... Args>
    T JsonConfig::get(Args... args) const
    {
        return get<T>(config_, args...);
    }

    template<typename T>
    T JsonConfig::get(const nlohmann::json& json, const char* name) const
    {
        return json[name];
    }

    template<typename T, typename... Args>
    T JsonConfig::get(const nlohmann::json& json, const char* first, Args... args) const
    {
        return get<T>(json[first], args...);
    }

} // photonmapping

#endif // CONFIG_H_