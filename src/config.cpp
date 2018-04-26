
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

    std::map<std::string, long> mBlockNames;
}

void Config::initConfig()
{
    // sem je potřeba dodat případ, kdy není zmáčklý žádný čudlík (zmáčknu čudlík a pak volbu zruším musí poslat -1)
    //mBlockNames.insert( std::make_pair("nic", -1) );
    //mf_2I1O.insert( std::make_pair(0, [](double a,double b){return a+b;}) );

    mBlockNames.insert( std::make_pair("adder", 0) );
    mf_2I1O.insert( std::make_pair(0, [](double a,double b){return a+b;}) );
    mIn.insert( std::make_pair(0, std::vector<std::string>{"general", "general"}) );
    mOut.insert( std::make_pair(0, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("subtractor", 1) );
    mf_2I1O.insert( std::make_pair(1, [](double a,double b){return a*b;}) );
    mIn.insert( std::make_pair(1, std::vector<std::string>{"general", "general"}) );
    mOut.insert( std::make_pair(1, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("multiplier", 2) );
    mf_1I1O.insert( std::make_pair(2, [](double x){return sqrt(x);}) );
    mIn.insert( std::make_pair(2, std::vector<std::string>{"general"}) );
    mOut.insert( std::make_pair(2, std::vector<std::string>{"general"}) );
}

BlockType Config::decodeBlockType(long key) {
    if(mf_2I1O.count(key) > 0) return BlockType::TwoIn_OneOut;
    else if(mf_1I1O.count(key) > 0) return BlockType::OneIn_OneOut;
    else throw MyError("Unknown block key", ErrorType::BlockError);
}

std::function<double(double,double)> Config::getFunc_2I1O(long key)
{
    try { return mf_2I1O.at(key); }
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

std::map<std::string, long>& Config::getBlockNames() { return mBlockNames; }
std::string Config::getImagePath(std::string s) { return ".." + PathSep + "examples" + PathSep + s + ".png"; }
std::string Config::getBlockName(long key) 
{ 
    for(auto& it: mBlockNames) 
        if(it.second == key) 
            return it.first; 
    throw MyError("Unknown block key", ErrorType::BlockError);
}