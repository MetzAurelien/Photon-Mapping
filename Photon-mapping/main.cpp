#include <exception>
#include <iostream>

int main()
{
    enum { kExitSuccess = 0, kExitFailure = 1 };

    try
    {
    }

    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return kExitFailure;
    }

    return kExitSuccess;
}