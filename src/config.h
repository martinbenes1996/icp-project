#ifndef CONFIG_H
#define CONFIG_H

#include <functional>

namespace Config
{
    std::function<double(double, double)> get2I1OFunction(long type);
    std::function<double(double)> get1I1OFunction(long type);

    std::string getGType();
}

#endif // CONFIG_H