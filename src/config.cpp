// config.cpp
// Autoři: xbenes49, xpolan09
// Projekt do předmětu ICP.
// Datum: 29.04.5018


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
    std::set<std::string> mTypes;
}

void Config::initConfig()
{
    mTypes.insert("general");
    
    // sem je potřeba dodat případ, kdy není zmáčklý žádný čudlík (zmáčknu čudlík a pak volbu zruším musí poslat -1)
    //mBlockNames.insert( std::make_pair("nic", -1) );
    //mf_2I1O.insert( std::make_pair(0, [](double a,double b){return a+b;}) );
    int id = 0;
    mBlockNames.insert( std::make_pair("adder", id) );
    mf_2I1O.insert( std::make_pair(id, [](double a,double b){return a+b;}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general", "general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("subtractor", id) );
    mf_2I1O.insert( std::make_pair(id, [](double a,double b){return a*b;}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general", "general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("multiplier", id) );
    mf_2I1O.insert( std::make_pair(id, [](double x,double y){return x*y;}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general", "general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("divider", id) );
    mf_2I1O.insert( std::make_pair(id, [](double x,double y){return x/y;}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general", "general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("ex", id) );
    mf_1I1O.insert( std::make_pair(id, [](double x){return pow(2.718281,x);}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("abs", id) );
    mf_1I1O.insert( std::make_pair(id, [](double x){return abs(x);}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("ln", id) );
    mf_1I1O.insert( std::make_pair(id, [](double x){return log(x);}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("neg", id) );
    mf_1I1O.insert( std::make_pair(id, [](double x){return -x;}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("sign", id) );
    mf_1I1O.insert( std::make_pair(id, [](double x){return (x>0)?1:((x<0)?-1:0);}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("squared", id) );
    mf_1I1O.insert( std::make_pair(id, [](double x){return x*x;}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

    mBlockNames.insert( std::make_pair("sqrt", id) );
    mf_1I1O.insert( std::make_pair(id, [](double x){return sqrt(x);}) );
    mIn.insert( std::make_pair(id, std::vector<std::string>{"general"}) );
    mOut.insert( std::make_pair(id++, std::vector<std::string>{"general"}) );

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
std::string Config::getHLImagePath(std::string s) { return ".." + PathSep + "examples" + PathSep + s + "_hl.png"; }
std::string Config::getBlockName(long key)
{
    for(auto& it: mBlockNames)
        if(it.second == key)
            return it.first;
    throw MyError("Unknown block key", ErrorType::BlockError);
}

void Config::addType(std::string type) { mTypes.insert(type); }
void Config::removeType(std::string type) { mTypes.erase(type); }
std::set<std::string> Config::getTypes() { return mTypes; }