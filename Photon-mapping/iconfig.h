#ifndef ICONFIG_H_
#define ICONFIG_H_

namespace photonmapping
{

    class IConfig
    {
    public:

        IConfig(const IConfig&) = delete;
        IConfig& operator=(const IConfig&) = delete;

        virtual void load(const char* filename) = 0;

        template<typename T, typename... Args>
        T get(Args...) const = 0;
    
    protected:

        IConfig() {}
    };

} // namespace photonmapping

#endif // CONFIG_H_