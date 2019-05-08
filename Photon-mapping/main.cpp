#include <exception>
#include <iostream>

#include <types.h>

int main()
{
    try
    {
    }

    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return photonmapping::kFailure;
    }

    return photonmapping::kSuccess;
}