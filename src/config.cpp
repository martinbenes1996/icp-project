
#include <iostream>
#include <map>
#include <cmath>

#include "config.h"
#include "defs.h"

namespace
{
    std::map<long, std::function<double(double, double)>> mf_2I1O;
    std::map<long, std::function<double(double)>> mf_1I1O;
    std::map<long, std::vector<std::string>> mIn;
    std::map<long, std::vector<std::string>> mOut;

    std::vector<std::string> mBlockNames {"prvni", "druhy", "treti", "ctvrty"};
}

void Config::initConfig()
{
    mf_2I1O.insert( std::make_pair(0, [](double a,double b){return a+b;}) );
    mf_2I1O.insert( std::make_pair(1, [](double a,double b){return a*b;}) );

    mf_1I1O.insert( std::make_pair(0, [](double x){return sqrt(x);}) );
}

std::function<double(double,double)> Config::getFunc_2I1O(long type)
{
    try { return mf_2I1O.at(type); }
    catch(std::out_of_range& e) { throw MyError("Unknown block type", ErrorType::BlockError); }
}

std::function<double(double)> Config::getFunc_1I1O(long type)
{
    try { return mf_1I1O.at(type); }
    catch(std::out_of_range& e) { throw MyError("Unknown block type", ErrorType::BlockError); }
}

std::vector<std::string> Config::getInput(long type)
{
    try { return mIn.at(type); }
    catch(std::out_of_range& e) { throw MyError("Unknown block type", ErrorType::BlockError); }
}
std::vector<std::string> Config::getOutput(long type)
{
    try { return mOut.at(type); }
    catch(std::out_of_range& e) { throw MyError("Unknown block type", ErrorType::BlockError); }
}

std::string Config::getGType() { return "general"; }

std::vector<std::string> Config::getBlockNames() { return mBlockNames; }