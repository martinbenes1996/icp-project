
#include <map>

#include "config.h"
#include "defs.h"

namespace
{
    std::map<long, std::function<double(double, double)>> m2I1Of;
    std::map<long, std::function<double(double)>> m1I1Of;
}

std::function<double(double, double)> Config::get2I1OFunction(long type)
{
    try { return m2I1Of.at(type); }
    catch(std::out_of_range& e) { throw MyError("Unknown block type", ErrorType::BlockError); }
}

std::function<double(double)> Config::get1I1OFunction(long type)
{
    try { return m1I1Of.at(type); }
    catch(std::out_of_range& e) { throw MyError("Unknown block type", ErrorType::BlockError); }
}

std::string Config::getGType() { return "general"; }