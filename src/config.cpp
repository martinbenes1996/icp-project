
#include <iostream>
#include <cmath>

#include "config.h"
#include "defs.h"

namespace
{
    std::map<long, std::function<double(double, double)>> mf_2I1O;
    std::map<long, std::function<double(double)>> mf_1I1O;
    std::map<long, std::vector<std::string>> mIn;
    std::map<long, std::vector<std::string>> mOut;

    std::map<long, std::string> mBlockNames;
}

#define BTYPE_EMPTY 0x00
#define BTYPE_2I1O  0x01
#define BTYPE_1I1O  0x02

void Config::initConfig()
{

    mf_2I1O.insert( std::make_pair(0, [](double a,double b){return a+b;}) );


    mf_2I1O.insert( std::make_pair(1, [](double a,double b){return a*b;}) );

    mf_1I1O.insert( std::make_pair(0, [](double x){return sqrt(x);}) );
}

BlockType Config::decodeBlockType(long key)
{
         if(key & BTYPE_2I1O) return BlockType::TwoIn_OneOut;
    else if(key & BTYPE_1I1O) return BlockType::OneIn_OneOut;
    else throw MyError("Unknown block key", ErrorType::BlockError);
}

std::function<double(double,double)> Config::getFunc_2I1O(long key)
{
    try { return mf_2I1O.at(key & ~(long)0xFF; }
    catch(std::out_of_range& e) { throw MyError("Unknown block key", ErrorType::BlockError); }
}

std::function<double(double)> Config::getFunc_1I1O(long key)
{
    try { return mf_1I1O.at(key); }
    catch(std::out_of_range& e) { throw MyError("Unknown block key", ErrorType::BlockError); }
}

std::vector<std::string> Config::getInput(long key)
{
    try { return mIn.at(key); }
    catch(std::out_of_range& e) { throw MyError("Unknown block type", ErrorType::BlockError); }
}
std::vector<std::string> Config::getOutput(long key)
{
    try { return mOut.at(key); }
    catch(std::out_of_range& e) { throw MyError("Unknown block type", ErrorType::BlockError); }
}

std::string Config::getGType() { return "general"; }

std::map<long, std::string> Config::getBlockNames() { return mBlockNames; }